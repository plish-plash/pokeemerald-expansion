#include "global.h"
#include "battle_setup.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "event_data.h"
#include "fieldmap.h"
#include "fishing.h"
#include "follower_npc.h"
#include "random.h"
#include "field_player_avatar.h"
#include "link.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "ow_abilities.h"
#include "pokeblock.h"
#include "pokemon.h"
#include "random.h"
#include "roamer.h"
#include "rtc.h"
#include "safari_zone.h"
#include "script.h"
#include "tv.h"
#include "wild_encounter.h"
#include "battle_debug.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "constants/abilities.h"
#include "constants/game_stat.h"
#include "constants/item.h"
#include "constants/items.h"
#include "constants/layouts.h"
#include "constants/map_types.h"
#include "constants/weather.h"

extern const u8 EventScript_SprayWoreOff[];

#define MAX_ENCOUNTER_RATE 2880

#define LAND_ENCOUNTER_RATE 20
#define WATER_ENCOUNTER_RATE 4
#define ROCKS_ENCOUNTER_RATE 30

static void ApplyFluteEncounterRateMod(u32 *encRate);
static void ApplyCleanseTagEncounterRateMod(u32 *encRate);

EWRAM_DATA static u8 sWildEncountersDisabled = 0;
EWRAM_DATA u8 gChainFishingDexNavStreak = 0;
EWRAM_DATA u8 gEncounterArea = WILD_AREA_LAND;

#include "data/map_habitat.h"

void DisableWildEncounters(bool8 disabled)
{
    sWildEncountersDisabled = disabled;
}

u8 ChooseWildMonLevel(u8 area, u8 min, u8 max)
{
    u8 range;
    u8 rand;

    if (LURE_STEP_COUNT == 0)
    {
        range = max - min + 1;
        rand = Random() % range;

        // check ability for max level mon
        if (!GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SANITY_IS_EGG))
        {
            u16 ability = GetMonAbility(&gParties[B_TRAINER_PLAYER][0]);
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

static u8 PickWildMonNature(enum Species species)
{
    u8 i;
    struct Pokeblock *safariPokeblock;
    u8 natures[NUM_NATURES];

    if (GetSafariZoneFlag() == TRUE && Random() % 100 < 80)
    {
        safariPokeblock = SafariZoneGetActivePokeblock();
        if (safariPokeblock != NULL)
        {
            for (i = 0; i < NUM_NATURES; i++)
                natures[i] = i;
            Shuffle(natures, NUM_NATURES, sizeof(natures[0]));
            for (i = 0; i < NUM_NATURES; i++)
            {
                if (PokeblockGetGain(natures[i], safariPokeblock) > 0)
                    return natures[i];
            }
        }
    }

    return GetSynchronizedNature(WILDMON_ORIGIN, species);
}

void CreateWildMon(enum Species species, u8 level)
{
    ZeroEnemyPartyMons();
    u32 personality = GetMonPersonality(species, GetSynchronizedGender(WILDMON_ORIGIN, species), PickWildMonNature(species), RANDOM_UNOWN_LETTER);
    CreateMonWithIVs(&gParties[B_TRAINER_OPPONENT_A][0], species, level, personality, OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
    GiveMonInitialMoveset(&gParties[B_TRAINER_OPPONENT_A][0]);
}

static bool8 CheckAbilityInfluence(u8 type, u8 ability, u8 *wildMonType)
{
    if (GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SANITY_IS_EGG))
        return FALSE;
    else if (GetMonAbility(&gParties[B_TRAINER_PLAYER][0]) != ability)
        return FALSE;
    else if (Random() % 2 != 0)
        return FALSE;

    *wildMonType = type;
    return TRUE;
}

static bool8 CheckWildMonSpecies(u16 species, u8 area, u8 levelMin, u8 levelMax, u8 type, u8 biome)
{
    enum TimeOfDay timeOfDay;

    // TODO weather
    // if gSaveBlock1Ptr->weather == WEATHER_SNOW

    if (gSpeciesInfo[species].isFrontierBanned)
        return FALSE;
    if (levelMin > gSpeciesLevelRange[species][1] || levelMax < gSpeciesLevelRange[species][0])
        return FALSE;
    if (type != TYPE_NONE)
        if (!(gSpeciesInfo[species].types[0] == type || gSpeciesInfo[species].types[1] == type))
            return FALSE;

    timeOfDay = GetTimeOfDay();
    if ((gSpeciesHabitat[species].flags & HABITAT_DAY) && timeOfDay != TIME_DAY)
        return FALSE;
    if ((gSpeciesHabitat[species].flags & HABITAT_NIGHT) && timeOfDay != TIME_NIGHT)
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

u16 GetMapHabitatIndex()
{
    u16 i;
    for (i = 0; ; i++)
    {
        if (gMapHabitat[i].mapGroup == MAP_GROUP(MAP_UNDEFINED) ||
         (gSaveBlock1Ptr->location.mapGroup == gMapHabitat[i].mapGroup
         && gSaveBlock1Ptr->location.mapNum == gMapHabitat[i].mapNum))
        {
            return i;
        }
    }
}

static u16 PickWildMonSpecies(u8 area, u8 type, u8 levelMin, u8 levelMax, u8 biome)
{
    u16 i;
    u16 species = SPECIES_NONE;
    u16 speciesIndex = 0;
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
    return species;
}

static bool8 TryGenerateWildMonInternal(u8 area, u8 flags, u8 type, u8 levelMin, u8 levelMax, u8 biome)
{
    u16 species;
    u8 level;

    species = PickWildMonSpecies(area, type, levelMin, levelMax, biome);
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
        IncrementGameStat(GAME_STAT_FISHING_ENCOUNTERS);
        SetPokemonAnglerSpecies(species);
    }
    return TRUE;
}

bool8 TryGenerateWildMon(u8 area, u8 flags)
{
    u8 type = TYPE_NONE;
    u8 levelMin, levelMax;
    u16 habitatIndex;
    u8 biome;

    habitatIndex = GetMapHabitatIndex();
    if (gMapHabitat[habitatIndex].levelMin == 0) return FALSE;
    levelMin = gMapHabitat[habitatIndex].levelMin;
    levelMax = gMapHabitat[habitatIndex].levelMax;

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
    else
    {
        biome = gMapHabitat[habitatIndex].biome;
    }

    return TryGenerateWildMonInternal(area, flags, type, levelMin, levelMax, biome);
}

static bool8 TryGenerateFishingWildMon(u8 rod)
{
    u8 levelMin, levelMax;

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

    return TryGenerateWildMonInternal(WILD_AREA_FISHING, 0, TYPE_NONE, levelMin, levelMax, BIOME_ANY);
}

bool8 SetUpMassOutbreakEncounter(u8 flags)
{
    u16 i;

    if (flags & WILD_CHECK_REPEL && !IsWildLevelAllowedByRepel(gSaveBlock1Ptr->outbreakPokemonLevel))
        return FALSE;

    CreateWildMon(gSaveBlock1Ptr->outbreakPokemonSpecies, gSaveBlock1Ptr->outbreakPokemonLevel);
    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(&gParties[B_TRAINER_OPPONENT_A][0], gSaveBlock1Ptr->outbreakPokemonMoves[i], i);

    return TRUE;
}

bool8 DoMassOutbreakEncounterTest(void)
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
    if (!ignoreAbility && !GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SANITY_IS_EGG))
    {
        enum Ability ability = GetMonAbility(&gParties[B_TRAINER_PLAYER][0]);

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
        else if (ability == ABILITY_INFILTRATOR && OW_INFILTRATOR >= GEN_8)
            encounterRate /= 2;
        else if (ability == ABILITY_NO_GUARD)
            encounterRate *= 2;
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

bool8 AreLegendariesInSootopolisPreventingEncounters(void)
{
    if (gSaveBlock1Ptr->location.mapGroup != MAP_GROUP(MAP_SOOTOPOLIS_CITY)
     || gSaveBlock1Ptr->location.mapNum != MAP_NUM(MAP_SOOTOPOLIS_CITY))
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
        else if (WildEncounterCheck(LAND_ENCOUNTER_RATE, FALSE) != TRUE)
            return FALSE;
        else if (TryGenerateWildMon(WILD_AREA_LAND, WILD_CHECK_KEEN_EYE) != TRUE)
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
        else if (WildEncounterCheck(LAND_ENCOUNTER_RATE, FALSE) != TRUE)
            return FALSE;
        else if (TryGenerateWildMon(WILD_AREA_LAND, WILD_CHECK_KEEN_EYE) != TRUE)
            return FALSE;

        GenerateBattlePyramidWildMon(SPECIES_NONE);
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

            if (TryStartRoamerEncounter())
            {
                roamer = &gSaveBlock1Ptr->roamer[gEncounteredRoamerIndex];
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
                        struct Pokemon mon1 = gParties[B_TRAINER_OPPONENT_A][0];
                        TryGenerateWildMon(WILD_AREA_LAND, WILD_CHECK_KEEN_EYE);
                        gParties[B_TRAINER_OPPONENT_A][1] = mon1;
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
        roamer = &gSaveBlock1Ptr->roamer[gEncounteredRoamerIndex];
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
                struct Pokemon mon1 = gParties[B_TRAINER_OPPONENT_A][0];
                TryGenerateWildMon(area, WILD_CHECK_KEEN_EYE);
                gParties[B_TRAINER_OPPONENT_A][1] = mon1;
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

u16 GetLocalWildMon(bool8 *isWaterMon)
{
    u16 habitatIndex = GetMapHabitatIndex();
    if (gMapHabitat[habitatIndex].levelMin == 0) return SPECIES_NONE;
    *isWaterMon = FALSE;
    return PickWildMonSpecies(WILD_AREA_LAND, TYPE_NONE, gMapHabitat[habitatIndex].levelMin, gMapHabitat[habitatIndex].levelMax, gMapHabitat[habitatIndex].biome);
}

u16 GetLocalWaterMon(void)
{
    u16 habitatIndex = GetMapHabitatIndex();
    if (gMapHabitat[habitatIndex].levelMin == 0) return SPECIES_NONE;
    return PickWildMonSpecies(WILD_AREA_WATER, TYPE_NONE, gMapHabitat[habitatIndex].levelMin, gMapHabitat[habitatIndex].levelMax, gMapHabitat[habitatIndex].biome);
}

bool8 UpdateRepelCounter(void)
{
    u16 repelLureVar = VarGet(VAR_REPEL_STEP_COUNT);
    u16 steps = REPEL_LURE_STEPS(repelLureVar);
    bool32 isLure = IS_LAST_USED_LURE(repelLureVar);

    if (InBattlePike() || CurrentBattlePyramidLocation() != PYRAMID_LOCATION_NONE)
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
                ScriptContext_SetupScript(EventScript_SprayWoreOff);
                return TRUE;
            }
        }
        else
        {
            VarSet(VAR_REPEL_STEP_COUNT, steps | REPEL_LURE_MASK);
            if (steps == 0)
            {
                ScriptContext_SetupScript(EventScript_SprayWoreOff);
                return TRUE;
            }
        }

    }
    return FALSE;
}

bool8 IsWildLevelAllowedByRepel(u8 wildLevel)
{
    u8 i;

    if (!REPEL_STEP_COUNT)
        return TRUE;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (I_REPEL_INCLUDE_FAINTED == GEN_1 || I_REPEL_INCLUDE_FAINTED >= GEN_6 || GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_HP))
        {
            if (!GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_IS_EGG))
                return wildLevel >= GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_LEVEL);
        }
    }

    return FALSE;
}

bool8 IsAbilityAllowingEncounter(u8 level)
{
    enum Ability ability;

    if (GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SANITY_IS_EGG))
        return TRUE;

    ability = GetMonAbility(&gParties[B_TRAINER_PLAYER][0]);
    if (ability == ABILITY_KEEN_EYE || ability == ABILITY_INTIMIDATE)
    {
        u8 playerMonLevel = GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL);
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
    if (GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM) == ITEM_CLEANSE_TAG)
        *encRate = *encRate * 2 / 3;
}

bool8 TryDoDoubleWildBattle(void)
{
    if (GetSafariZoneFlag()
      || (WE_DOUBLE_WILD_REQUIRE_2_MONS && GetMonsStateToDoubles() != PLAYER_HAS_TWO_USABLE_MONS))
        return FALSE;
    if (FollowerNPCIsBattlePartner() && FNPC_FLAG_PARTNER_WILD_BATTLES != 0
     && (FNPC_FLAG_PARTNER_WILD_BATTLES == FNPC_ALWAYS || FlagGet(FNPC_FLAG_PARTNER_WILD_BATTLES)) && FNPC_NPC_FOLLOWER_WILD_BATTLE_VS_2 == TRUE)
        return TRUE;
    else if (FlagGet(WE_FLAG_FORCE_DOUBLE_WILD))
        return TRUE;
    else if (RandomPercentage(RNG_NONE, WE_DOUBLE_WILD_CHANCE))
        return TRUE;
    return FALSE;
}

bool8 StandardWildEncounter_Debug(void)
{
    if (TryGenerateWildMon(WILD_AREA_LAND, 0) != TRUE)
        return FALSE;

    DoStandardWildBattle_Debug();
    return TRUE;
}

bool32 MapHasNoEncounterData(void)
{
    return FALSE;
}
