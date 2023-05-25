#include "global.h"
#include "wild_encounter.h"
#include "pokemon.h"
#include "metatile_behavior.h"
#include "fieldmap.h"
#include "random.h"
#include "field_player_avatar.h"
#include "event_data.h"
#include "safari_zone.h"
#include "overworld.h"
#include "pokeblock.h"
#include "battle_setup.h"
#include "roamer.h"
#include "tv.h"
#include "link.h"
#include "script.h"
#include "battle_debug.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "rtc.h"
#include "constants/abilities.h"
#include "constants/game_stat.h"
#include "constants/item.h"
#include "constants/items.h"
#include "constants/layouts.h"
#include "constants/map_types.h"
#include "constants/weather.h"

#include "data/map_habitat.h"

extern const u8 EventScript_RepelWoreOff[];
extern const u8 EventScript_LureWoreOff[];

#define MAX_ENCOUNTER_RATE 2880
#define LAND_ENCOUNTER_RATE 20
#define WATER_ENCOUNTER_RATE 4
#define ROCKS_ENCOUNTER_RATE 30

#define WILD_CHECK_REPEL    (1 << 0)
#define WILD_CHECK_KEEN_EYE (1 << 1)

#define HEADER_NONE 0xFFFF

static bool8 IsWildLevelAllowedByRepel(u8 level);
static void ApplyFluteEncounterRateMod(u32 *encRate);
static void ApplyCleanseTagEncounterRateMod(u32 *encRate);
static bool8 IsAbilityAllowingEncounter(u8 level);

EWRAM_DATA static u8 sWildEncountersDisabled = 0;
EWRAM_DATA u8 gEncounterArea = WILD_AREA_LAND;

void DisableWildEncounters(bool8 disabled)
{
    sWildEncountersDisabled = disabled;
}

static const u16 sBadgeFlags[NUM_BADGES] =
{
    FLAG_BADGE01_GET,
    FLAG_BADGE02_GET,
    FLAG_BADGE03_GET,
    FLAG_BADGE04_GET,
    FLAG_BADGE05_GET,
    FLAG_BADGE06_GET,
    FLAG_BADGE07_GET,
    FLAG_BADGE08_GET,
};

static int GetNumOwnedBadges(void)
{
    u32 i;

    for (i = 0; i < NUM_BADGES; i++)
    {
        if (!FlagGet(sBadgeFlags[i]))
            break;
    }

    return i;
}

static u8 ChooseWildMonLevel(u8 area, u8 min, u8 max)
{
    u8 range;
    u8 rand;

    if (LURE_STEP_COUNT == 0)
    {
        range = max - min + 1;
        rand = Random() % range;

        // check ability for max level mon
        if (!GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
        {
            u16 ability = GetMonAbility(&gPlayerParty[0]);
            if (ability == ABILITY_HUSTLE || ability == ABILITY_VITAL_SPIRIT || ability == ABILITY_PRESSURE)
            {
                if (Random() % 2 == 0)
                    return max;

                if (rand != 0)
                    rand--;
            }
        }
        return min + rand;
    }
    else
    {
        return max;
    }
}

static u8 PickWildMonNature(void)
{
    u8 i;
    u8 j;
    struct Pokeblock *safariPokeblock;
    u8 natures[NUM_NATURES];

    if (GetSafariZoneFlag() == TRUE && Random() % 100 < 80)
    {
        safariPokeblock = SafariZoneGetActivePokeblock();
        if (safariPokeblock != NULL)
        {
            for (i = 0; i < NUM_NATURES; i++)
                natures[i] = i;
            for (i = 0; i < NUM_NATURES - 1; i++)
            {
                for (j = i + 1; j < NUM_NATURES; j++)
                {
                    if (Random() & 1)
                    {
                        u8 temp;
                        SWAP(natures[i], natures[j], temp);
                    }
                }
            }
            for (i = 0; i < NUM_NATURES; i++)
            {
                if (PokeblockGetGain(natures[i], safariPokeblock) > 0)
                    return natures[i];
            }
        }
    }
    // check synchronize for a pokemon with the same ability
    if (!GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG)
        && GetMonAbility(&gPlayerParty[0]) == ABILITY_SYNCHRONIZE
    #if B_SYNCHRONIZE_NATURE <= GEN_7
        && (Random() % 2 == 0)
    #endif
    )
    {
        return GetMonData(&gPlayerParty[0], MON_DATA_PERSONALITY) % NUM_NATURES;
    }

    // random nature
    return Random() % NUM_NATURES;
}

static void CreateWildMon(u16 species, u8 level)
{
    bool32 checkCuteCharm;

    ZeroEnemyPartyMons();
    checkCuteCharm = TRUE;

    switch (gSpeciesInfo[species].genderRatio)
    {
    case MON_MALE:
    case MON_FEMALE:
    case MON_GENDERLESS:
        checkCuteCharm = FALSE;
        break;
    }

    if (checkCuteCharm
        && !GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG)
        && GetMonAbility(&gPlayerParty[0]) == ABILITY_CUTE_CHARM
        && Random() % 3 != 0)
    {
        u16 leadingMonSpecies = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES);
        u32 leadingMonPersonality = GetMonData(&gPlayerParty[0], MON_DATA_PERSONALITY);
        u8 gender = GetGenderFromSpeciesAndPersonality(leadingMonSpecies, leadingMonPersonality);

        // misses mon is genderless check, although no genderless mon can have cute charm as ability
        if (gender == MON_FEMALE)
            gender = MON_MALE;
        else
            gender = MON_FEMALE;

        CreateMonWithGenderNatureLetter(&gEnemyParty[0], species, level, USE_RANDOM_IVS, gender, PickWildMonNature(), 0);
        return;
    }

    CreateMonWithNature(&gEnemyParty[0], species, level, USE_RANDOM_IVS, PickWildMonNature());
}

static bool8 CheckAbilityInfluence(u8 type, u8 ability, u8 *wildMonType)
{
    if (GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
        return FALSE;
    else if (GetMonAbility(&gPlayerParty[0]) != ability)
        return FALSE;
    else if (Random() % 2 != 0)
        return FALSE;

    *wildMonType = type;
    return TRUE;
}

static bool8 CheckWildMonSpecies(u16 species, u8 area, u8 levelMin, u8 levelMax, u8 type, u8 biome)
{
    bool8 isNight;

    // TODO weather
    // if gSaveBlock1Ptr->weather == WEATHER_SNOW

    if (gSpeciesInfo[species].flags != 0) // Legendary, mythical, ultra beast, etc.
        return FALSE;
    if (levelMin > gSpeciesLevelRange[species][1] || levelMax < gSpeciesLevelRange[species][0])
        return FALSE;
    if (type != TYPE_NONE)
        if (!(gSpeciesInfo[species].types[0] == type || gSpeciesInfo[species].types[1] == type))
            return FALSE;

    isNight = (gLocalTime.hours <= 6 || gLocalTime.hours >= 19);
    if ((gSpeciesHabitat[species].flags & HABITAT_DAY) && isNight)
        return FALSE;
    if ((gSpeciesHabitat[species].flags & HABITAT_NIGHT) && !isNight)
        return FALSE;

    if (biome != BIOME_ANY && gSpeciesHabitat[species].biome != BIOME_ANY && gSpeciesHabitat[species].biome != biome)
        return FALSE;

    switch (area)
    {
    case WILD_AREA_LAND:
        if (gMapHeader.cave || gMapHeader.mapType == MAP_TYPE_UNDERGROUND)
        {
            if (gSpeciesHabitat[species].flags & HABITAT_CAVE)
                return TRUE;
        }
        else
        {
            if (gSpeciesHabitat[species].flags & HABITAT_LAND)
                return TRUE;
        }
        break;
    case WILD_AREA_WATER:
        return (gSpeciesHabitat[species].flags & HABITAT_WATER);
    case WILD_AREA_ROCKS:
        return (gSpeciesHabitat[species].encounter == HABITAT_ENCOUNTER_ROCK_SMASH);
    case WILD_AREA_FISHING:
        return (gSpeciesHabitat[species].encounter == HABITAT_ENCOUNTER_FISHING);
    case WILD_AREA_SKY:
        return (gSpeciesHabitat[species].encounter == HABITAT_ENCOUNTER_FLYING);
    case WILD_AREA_CHALLENGE:
        return (gSpeciesHabitat[species].encounter == HABITAT_ENCOUNTER_FIGHTING);
    case WILD_AREA_MAGNET:
        return (gSpeciesHabitat[species].encounter == HABITAT_ENCOUNTER_STEEL);
    case WILD_AREA_PSYCHIC:
        return (gSpeciesHabitat[species].encounter == HABITAT_ENCOUNTER_PSYCHIC);
    }
    return FALSE;
}

static void FixWildMonLevel(u16 species, u8 *levelMin, u8 *levelMax)
{
    u8 speciesMin = gSpeciesLevelRange[species][0];
    u8 speciesMax = gSpeciesLevelRange[species][1];
    if (*levelMin < speciesMin) *levelMin = speciesMin;
    if (*levelMax > speciesMax) *levelMax = speciesMax;
    if (*levelMax < *levelMin) *levelMax = *levelMin;
}

static u16 GetMapHabitatIndex()
{
    u16 i;
    for (i = 0; ; i++)
    {
        if (gMapHabitat[i].mapGroup == MAP_GROUPS_COUNT ||
         (gSaveBlock1Ptr->location.mapGroup == gMapHabitat[i].mapGroup
         && gSaveBlock1Ptr->location.mapNum == gMapHabitat[i].mapNum))
        {
            return i;
        }
    }
}

static bool8 TryGenerateWildMonInternal(u8 area, u8 flags, u8 type, u8 levelMin, u8 levelMax, u8 biome)
{
    u16 i;
    u16 species = SPECIES_NONE;
    u16 speciesIndex = 0;
    u8 level;

    for (i = 1; i < NUM_WILD_SPECIES; i++)
    {
        if (CheckWildMonSpecies(i, area, levelMin, levelMax, type, biome))
        {
            speciesIndex++;
        }
    }
    if (speciesIndex == 0)
        return FALSE;

    speciesIndex = Random() % speciesIndex;
    for (i = 1; i < NUM_WILD_SPECIES; i++)
    {
        if (CheckWildMonSpecies(i, area, levelMin, levelMax, type, biome))
        {
            if (speciesIndex == 0)
            {
                species = i;
                break;
            }
            else
            {
                speciesIndex--;
            }
        }
    }
    if (species == SPECIES_NONE)
        return FALSE;
    
    FixWildMonLevel(species, &levelMin, &levelMax);
    level = ChooseWildMonLevel(area, levelMin, levelMax);
    if (level < 2) level = 2;

    if (flags & WILD_CHECK_REPEL && !IsWildLevelAllowedByRepel(level))
        return FALSE;
    if (gMapHeader.mapLayoutId != LAYOUT_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_WILD_MONS && flags & WILD_CHECK_KEEN_EYE && !IsAbilityAllowingEncounter(level))
        return FALSE;

    CreateWildMon(species, level);
    if (area == WILD_AREA_FISHING)
    {
        IncrementGameStat(GAME_STAT_FISHING_CAPTURES);
        SetPokemonAnglerSpecies(species);
    }
    return TRUE;
}

static bool8 TryGenerateWildMon(u8 area, u8 flags)
{
    u8 type = TYPE_NONE;
    u8 levelMin, levelMax;
    u8 numBadges;
    u16 habitatIndex;
    u8 biome;

    habitatIndex = GetMapHabitatIndex();
    if (gMapHabitat[habitatIndex].levelMin == 0) return FALSE;

    numBadges = GetNumOwnedBadges();
    levelMin = gMapHabitat[habitatIndex].levelMin + (numBadges * 2);
    levelMax = gMapHabitat[habitatIndex].levelMax + (numBadges * 3);

    if (area == WILD_AREA_LAND || area == WILD_AREA_WATER)
    {
        if (CheckAbilityInfluence(TYPE_STEEL, ABILITY_MAGNET_PULL, &type))
        {}
        else if (CheckAbilityInfluence(TYPE_ELECTRIC, ABILITY_STATIC, &type))
        {}
        else if (CheckAbilityInfluence(TYPE_ELECTRIC, ABILITY_LIGHTNING_ROD, &type))
        {}
        else if (CheckAbilityInfluence(TYPE_FIRE, ABILITY_FLASH_FIRE, &type))
        {}
        else if (CheckAbilityInfluence(TYPE_GRASS, ABILITY_HARVEST, &type))
        {}
        else if (CheckAbilityInfluence(TYPE_WATER, ABILITY_STORM_DRAIN, &type))
        {}
    }

    if (area == WILD_AREA_WATER)
    {
        biome = BIOME_ANY;
    }
    else if (gMapHeader.mapType == MAP_TYPE_TOWN || gMapHeader.mapType == MAP_TYPE_CITY)
    {
        biome = BIOME_URBAN;
    }
    else
    {
        biome = gMapHabitat[habitatIndex].biome;
    }

    return TryGenerateWildMonInternal(area, flags, type, levelMin, levelMax, biome);
}

static bool8 TryGenerateFishingWildMon(u8 rod)
{
    u8 levelMin, levelMax;
    u8 numBadges;

    switch (rod)
    {
    case OLD_ROD:
    default:
        levelMin = 5;
        levelMax = 10;
        break;
    case GOOD_ROD:
        levelMin = 10;
        levelMax = 30;
        break;
    case SUPER_ROD:
        levelMin = 30;
        levelMax = 50;
        break;
    }

    numBadges = GetNumOwnedBadges();
    levelMin += numBadges * 2;
    levelMax += numBadges * 4;
    return TryGenerateWildMonInternal(WILD_AREA_FISHING, 0, TYPE_NONE, levelMin, levelMax, BIOME_ANY);
}

static bool8 SetUpMassOutbreakEncounter(u8 flags)
{
    u16 i;

    if (flags & WILD_CHECK_REPEL && !IsWildLevelAllowedByRepel(gSaveBlock1Ptr->outbreakPokemonLevel))
        return FALSE;

    CreateWildMon(gSaveBlock1Ptr->outbreakPokemonSpecies, gSaveBlock1Ptr->outbreakPokemonLevel);
    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(&gEnemyParty[0], gSaveBlock1Ptr->outbreakPokemonMoves[i], i);

    return TRUE;
}

static bool8 DoMassOutbreakEncounterTest(void)
{
    if (gSaveBlock1Ptr->outbreakPokemonSpecies != SPECIES_NONE
     && gSaveBlock1Ptr->location.mapNum == gSaveBlock1Ptr->outbreakLocationMapNum
     && gSaveBlock1Ptr->location.mapGroup == gSaveBlock1Ptr->outbreakLocationMapGroup)
    {
        if (Random() % 100 < gSaveBlock1Ptr->outbreakPokemonProbability)
            return TRUE;
    }
    return FALSE;
}

static bool8 EncounterOddsCheck(u16 encounterRate)
{
    if (Random() % MAX_ENCOUNTER_RATE < encounterRate)
        return TRUE;
    else
        return FALSE;
}

// Returns true if it will try to create a wild encounter.
static bool8 WildEncounterCheck(u32 encounterRate, bool8 ignoreAbility)
{
    encounterRate *= 16;
    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE))
        encounterRate = encounterRate * 80 / 100;
    ApplyFluteEncounterRateMod(&encounterRate);
    ApplyCleanseTagEncounterRateMod(&encounterRate);
    if (LURE_STEP_COUNT != 0)
        encounterRate *= 2;
    if (!ignoreAbility && !GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
    {
        u32 ability = GetMonAbility(&gPlayerParty[0]);

        if (ability == ABILITY_STENCH && gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR)
            encounterRate = encounterRate * 3 / 4;
        else if (ability == ABILITY_STENCH)
            encounterRate /= 2;
        else if (ability == ABILITY_ILLUMINATE)
            encounterRate *= 2;
        else if (ability == ABILITY_WHITE_SMOKE)
            encounterRate /= 2;
        else if (ability == ABILITY_ARENA_TRAP)
            encounterRate *= 2;
        else if (ability == ABILITY_SAND_VEIL && gSaveBlock1Ptr->weather == WEATHER_SANDSTORM)
            encounterRate /= 2;
        else if (ability == ABILITY_SNOW_CLOAK && gSaveBlock1Ptr->weather == WEATHER_SNOW)
            encounterRate /= 2;
        else if (ability == ABILITY_QUICK_FEET)
            encounterRate /= 2;
        else if (ability == ABILITY_INFILTRATOR)
            encounterRate /= 2;
        else if (ability == ABILITY_NO_GUARD)
            encounterRate = encounterRate * 3 / 2;
    }
    if (encounterRate > MAX_ENCOUNTER_RATE)
        encounterRate = MAX_ENCOUNTER_RATE;
    return EncounterOddsCheck(encounterRate);
}

// When you first step on a different type of metatile, there's a 40% chance it
// skips the wild encounter check entirely.
static bool8 AllowWildCheckOnNewMetatile(void)
{
    if (Random() % 100 >= 60)
        return FALSE;
    else
        return TRUE;
}

static bool8 AreLegendariesInSootopolisPreventingEncounters(void)
{
    if (gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(SOOTOPOLIS_CITY)
     || gSaveBlock1Ptr->location.mapNum != MAP_NUM(SOOTOPOLIS_CITY))
    {
        return FALSE;
    }

    return FlagGet(FLAG_LEGENDARIES_IN_SOOTOPOLIS);
}

bool8 StandardWildEncounter(u16 curMetatileBehavior, u16 prevMetatileBehavior, bool8 checkRate)
{
    struct Roamer *roamer;

    if (sWildEncountersDisabled == TRUE)
        return FALSE;

    if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_WILD_MONS)
    {
        if (prevMetatileBehavior != curMetatileBehavior && !AllowWildCheckOnNewMetatile())
            return FALSE;
        else if (checkRate && WildEncounterCheck(10, FALSE) != TRUE)
            return FALSE;
        else if (!TryGenerateBattlePikeWildMon(TRUE))
            return FALSE;

        BattleSetup_StartBattlePikeWildBattle();
        return TRUE;
    }
    else if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR)
    {
        if (prevMetatileBehavior != curMetatileBehavior && !AllowWildCheckOnNewMetatile())
            return FALSE;
        else if (checkRate && WildEncounterCheck(5, FALSE) != TRUE)
            return FALSE;

        GenerateBattlePyramidWildMon();
        BattleSetup_StartWildBattle();
        return TRUE;
    }
    else
    {
        if (MetatileBehavior_IsLandWildEncounter(curMetatileBehavior) == TRUE)
        {
            if (prevMetatileBehavior != curMetatileBehavior && !AllowWildCheckOnNewMetatile())
                return FALSE;
            else if (checkRate && WildEncounterCheck(LAND_ENCOUNTER_RATE, FALSE) != TRUE)
                return FALSE;

            if (TryStartRoamerEncounter() == TRUE)
            {
                roamer = &gSaveBlock1Ptr->roamer;
                if (!IsWildLevelAllowedByRepel(roamer->level))
                    return FALSE;

                BattleSetup_StartRoamerBattle();
                return TRUE;
            }
            else
            {
                if (DoMassOutbreakEncounterTest() == TRUE && SetUpMassOutbreakEncounter(WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
                {
                    BattleSetup_StartWildBattle();
                    return TRUE;
                }

                // try a regular wild land encounter
                if (TryGenerateWildMon(WILD_AREA_LAND, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
                {
                    if (TryDoDoubleWildBattle())
                    {
                        struct Pokemon mon1 = gEnemyParty[0];
                        TryGenerateWildMon(WILD_AREA_LAND, WILD_CHECK_KEEN_EYE);
                        gEnemyParty[1] = mon1;
                        BattleSetup_StartDoubleWildBattle();
                    }
                    else
                    {
                        BattleSetup_StartWildBattle();
                    }
                    return TRUE;
                }

                return FALSE;
            }
        }
        else if (MetatileBehavior_IsWaterWildEncounter(curMetatileBehavior) == TRUE
                 || (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING) && MetatileBehavior_IsBridgeOverWater(curMetatileBehavior) == TRUE))
        {
            if (AreLegendariesInSootopolisPreventingEncounters() == TRUE)
                return FALSE;
            else if (prevMetatileBehavior != curMetatileBehavior && !AllowWildCheckOnNewMetatile())
                return FALSE;
                
            return HabitatWildEncounter(WILD_AREA_WATER, WATER_ENCOUNTER_RATE);
        }
    }

    return FALSE;
}

bool8 HabitatWildEncounter(u8 area, u32 encounterRate)
{
    struct Roamer *roamer;

    if (encounterRate > 0 && WildEncounterCheck(encounterRate, TRUE) != TRUE)
        return FALSE;

    if (TryStartRoamerEncounter() == TRUE)
    {
        roamer = &gSaveBlock1Ptr->roamer;
        if (!IsWildLevelAllowedByRepel(roamer->level))
            return FALSE;

        BattleSetup_StartRoamerBattle();
        return TRUE;
    }
    else
    {
        if (TryGenerateWildMon(area, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
        {
            gEncounterArea = area;
            if (TryDoDoubleWildBattle())
            {
                struct Pokemon mon1 = gEnemyParty[0];
                TryGenerateWildMon(area, WILD_CHECK_KEEN_EYE);
                gEnemyParty[1] = mon1;
                BattleSetup_StartDoubleWildBattle();
            }
            else
            {
                BattleSetup_StartWildBattle();
            }
            return TRUE;
        }

        return FALSE;
    }
}

void RockSmashWildEncounter(void)
{
    gSpecialVar_Result = HabitatWildEncounter(WILD_AREA_ROCKS, ROCKS_ENCOUNTER_RATE);
}

bool8 SweetScentWildEncounter(void)
{
    s16 x, y;
    u16 metatileBehavior;
    PlayerGetDestCoords(&x, &y);
    metatileBehavior = MapGridGetMetatileBehaviorAt(x, y);
    return StandardWildEncounter(metatileBehavior, metatileBehavior, FALSE);
}

bool8 FishingWildEncounter(u8 rod)
{
    if (TryGenerateFishingWildMon(rod))
    {
        gEncounterArea = WILD_AREA_FISHING;
        BattleSetup_StartWildBattle();
        return TRUE;
    }
    return FALSE;
}

// TODO these two functions are used to determine what ambient cries to play
u16 GetLocalWildMon(bool8 *isWaterMon)
{
    *isWaterMon = FALSE;
    return SPECIES_MEW;
}

u16 GetLocalWaterMon(void)
{
    return SPECIES_MEW;
}

bool8 UpdateRepelCounter(void)
{
    u16 repelLureVar = VarGet(VAR_REPEL_STEP_COUNT);
    u16 steps = REPEL_LURE_STEPS(repelLureVar);
    bool32 isLure = IS_LAST_USED_LURE(repelLureVar);

    if (InBattlePike() || InBattlePyramid())
        return FALSE;
    if (InUnionRoom() == TRUE)
        return FALSE;

    if (steps != 0)
    {
        steps--;
        if (!isLure)
        {
            VarSet(VAR_REPEL_STEP_COUNT, steps);
            if (steps == 0)
            {
                ScriptContext_SetupScript(EventScript_RepelWoreOff);
                return TRUE;
            }
        }
        else
        {
            VarSet(VAR_REPEL_STEP_COUNT, steps | REPEL_LURE_MASK);
            if (steps == 0)
            {
                ScriptContext_SetupScript(EventScript_LureWoreOff);
                return TRUE;
            }
        }

    }
    return FALSE;
}

static bool8 IsWildLevelAllowedByRepel(u8 wildLevel)
{
    u8 i;

    if (!REPEL_STEP_COUNT)
        return TRUE;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_HP) && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG))
        {
            u8 ourLevel = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL);

            if (wildLevel < ourLevel)
                return FALSE;
            else
                return TRUE;
        }
    }

    return FALSE;
}

static bool8 IsAbilityAllowingEncounter(u8 level)
{
    u16 ability;

    if (GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
        return TRUE;

    ability = GetMonAbility(&gPlayerParty[0]);
    if (ability == ABILITY_KEEN_EYE || ability == ABILITY_INTIMIDATE)
    {
        u8 playerMonLevel = GetMonData(&gPlayerParty[0], MON_DATA_LEVEL);
        if (playerMonLevel > 5 && level <= playerMonLevel - 5 && !(Random() % 2))
            return FALSE;
    }

    return TRUE;
}

static void ApplyFluteEncounterRateMod(u32 *encRate)
{
    if (FlagGet(FLAG_SYS_ENC_UP_ITEM) == TRUE)
        *encRate += *encRate / 2;
    else if (FlagGet(FLAG_SYS_ENC_DOWN_ITEM) == TRUE)
        *encRate = *encRate / 2;
}

static void ApplyCleanseTagEncounterRateMod(u32 *encRate)
{
    if (GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM) == ITEM_CLEANSE_TAG)
        *encRate = *encRate * 2 / 3;
}

bool8 TryDoDoubleWildBattle(void)
{
#if B_DOUBLE_WILD_REQUIRE_2_MONS == TRUE
    if (GetSafariZoneFlag() || GetMonsStateToDoubles() != PLAYER_HAS_TWO_USABLE_MONS)
#else
    if (GetSafariZoneFlag())
#endif
        return FALSE;
#if B_FLAG_FORCE_DOUBLE_WILD != 0
    else if (FlagGet(B_FLAG_FORCE_DOUBLE_WILD))
        return TRUE;
#endif
#if B_DOUBLE_WILD_CHANCE != 0
    else if ((Random() % 100) + 1 <= B_DOUBLE_WILD_CHANCE)
        return TRUE;
#endif
    return FALSE;
}
