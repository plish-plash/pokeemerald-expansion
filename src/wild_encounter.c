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
#include "constants/abilities.h"
#include "constants/game_stat.h"
#include "constants/item.h"
#include "constants/items.h"
#include "constants/layouts.h"
#include "constants/weather.h"
#include "item.h"

extern const u8 EventScript_RepelWoreOff[];
extern const u8 EventScript_LureWoreOff[];

#define MAX_ENCOUNTER_RATE 2880

#define NUM_WILD_SPECIES SPECIES_ENAMORUS + 1

enum {
    WILD_AREA_LAND,
    WILD_AREA_WATER,
    WILD_AREA_ROCKS,
    WILD_AREA_FISHING,
};

#define WILD_CHECK_REPEL    (1 << 0)
#define WILD_CHECK_KEEN_EYE (1 << 1)

#define HEADER_NONE 0xFFFF

static bool8 IsWildLevelAllowedByRepel(u8 level);
static void ApplyFluteEncounterRateMod(u32 *encRate);
static void ApplyCleanseTagEncounterRateMod(u32 *encRate);
static u8 GetMaxLevelOfSpeciesInWildTable(const struct WildPokemon *wildMon, u16 species, u8 area);
static bool8 CheckForAbilityInfluence(u16 ability);
static bool8 IsAbilityAllowingEncounter(u8 level);

EWRAM_DATA static u8 sWildEncountersDisabled = 0;
EWRAM_DATA bool8 gIsFishingEncounter = 0;
EWRAM_DATA bool8 gIsSurfingEncounter = 0;

#include "data/wild_encounters.h"
#include "data/pokemon/species_is_evolved.h"

void DisableWildEncounters(bool8 disabled)
{
    sWildEncountersDisabled = disabled;
}

static bool8 IsValidWildMonSpecies(u16 species, u8 requiredType, u8 secondaryType)
{
    const struct SpeciesInfo *speciesInfo = &gSpeciesInfo[species];
    if (gSpeciesIsEvolved[species])
        return FALSE;
    if (speciesInfo->flags != 0) // Legendary, mythical, ultra beast, etc.
        return FALSE;
    if (requiredType != TYPE_NONE)
        if (!(speciesInfo->types[0] == requiredType || speciesInfo->types[1] == requiredType))
            return FALSE;
    if (secondaryType != TYPE_NONE)
        if (!(speciesInfo->types[0] == secondaryType || speciesInfo->types[1] == secondaryType))
            return FALSE;
    return TRUE;
}

static u16 ChooseWildMonSpecies(u8 requiredType, u8 secondaryType)
{
    u16 i;
    u16 speciesIndex = 0;

    for (i = 1; i < NUM_WILD_SPECIES; i++)
    {
        if (IsValidWildMonSpecies(i, requiredType, secondaryType))
            speciesIndex++;
    }
    if (speciesIndex == 0)
    {
        if (secondaryType != TYPE_NONE)
            return ChooseWildMonSpecies(requiredType, TYPE_NONE);
        else
            return SPECIES_NONE;
    }

    speciesIndex = Random() % speciesIndex;
    for (i = 1; i < NUM_WILD_SPECIES; i++)
    {
        if (IsValidWildMonSpecies(i, requiredType, secondaryType))
        {
            if (speciesIndex == 0)
                return i;
            else
                speciesIndex--;
        }
    }
    return SPECIES_NONE;
}

static u8 GetWildMonTypeFromGemItem(void)
{
    if (CheckBagHasItem(ITEM_NORMAL_GEM, 1))
        return TYPE_NORMAL;
    else if (CheckBagHasItem(ITEM_FIRE_GEM, 1))
        return TYPE_FIRE;
    else if (CheckBagHasItem(ITEM_WATER_GEM, 1))
        return TYPE_WATER;
    else if (CheckBagHasItem(ITEM_ELECTRIC_GEM, 1))
        return TYPE_ELECTRIC;
    else if (CheckBagHasItem(ITEM_GRASS_GEM, 1))
        return TYPE_GRASS;
    else if (CheckBagHasItem(ITEM_ICE_GEM, 1))
        return TYPE_ICE;
    else if (CheckBagHasItem(ITEM_FIGHTING_GEM, 1))
        return TYPE_FIGHTING;
    else if (CheckBagHasItem(ITEM_POISON_GEM, 1))
        return TYPE_POISON;
    else if (CheckBagHasItem(ITEM_GROUND_GEM, 1))
        return TYPE_GROUND;
    else if (CheckBagHasItem(ITEM_FLYING_GEM, 1))
        return TYPE_FLYING;
    else if (CheckBagHasItem(ITEM_PSYCHIC_GEM, 1))
        return TYPE_PSYCHIC;
    else if (CheckBagHasItem(ITEM_BUG_GEM, 1))
        return TYPE_BUG;
    else if (CheckBagHasItem(ITEM_ROCK_GEM, 1))
        return TYPE_ROCK;
    else if (CheckBagHasItem(ITEM_GHOST_GEM, 1))
        return TYPE_GHOST;
    else if (CheckBagHasItem(ITEM_DRAGON_GEM, 1))
        return TYPE_DRAGON;
    else if (CheckBagHasItem(ITEM_DARK_GEM, 1))
        return TYPE_DARK;
    else if (CheckBagHasItem(ITEM_STEEL_GEM, 1))
        return TYPE_STEEL;
    else if (CheckBagHasItem(ITEM_FAIRY_GEM, 1))
        return TYPE_FAIRY;
    else
        return TYPE_NONE;
}

static u8 ChooseWildMonLevel(const struct WildPokemon *wildPokemon, u8 area)
{
    u8 min = 100;
    u8 max = 1;
    u8 range;
    u8 rand;
    u8 i, numMon = 0;
    
    switch (area)
    {
    case WILD_AREA_LAND:
        numMon = LAND_WILD_COUNT;
        break;
    case WILD_AREA_WATER:
        numMon = WATER_WILD_COUNT;
        break;
    case WILD_AREA_ROCKS:
        numMon = ROCK_WILD_COUNT;
        break;
    }

    for (i = 0; i < numMon; i++) {
        min = min(min, wildPokemon[i].minLevel);
        max = max(max, wildPokemon[i].maxLevel);
    }
    if (min > max) min = max;

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

static u8 ChooseWildMonLevelFishing(u8 rod)
{
    u8 min;
    u8 max;
    u8 range;
    u8 rand;

    switch (rod)
    {
    case OLD_ROD:
    default:
        min = 5;
        max = 10;
        break;
    case GOOD_ROD:
        min = 10;
        max = 30;
        break;
    case SUPER_ROD:
        min = 30;
        max = 50;
        break;
    }
    if (min > max) min = max;

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

static u16 GetCurrentMapWildMonHeaderId(void)
{
    u16 i;

    for (i = 0; ; i++)
    {
        const struct WildPokemonHeader *wildHeader = &gWildMonHeaders[i];
        if (wildHeader->mapGroup == MAP_GROUP(UNDEFINED))
            break;

        if (gWildMonHeaders[i].mapGroup == gSaveBlock1Ptr->location.mapGroup &&
            gWildMonHeaders[i].mapNum == gSaveBlock1Ptr->location.mapNum)
        {
            if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(ALTERING_CAVE) &&
                gSaveBlock1Ptr->location.mapNum == MAP_NUM(ALTERING_CAVE))
            {
                u16 alteringCaveId = VarGet(VAR_ALTERING_CAVE_WILD_SET);
                if (alteringCaveId >= NUM_ALTERING_CAVE_TABLES)
                    alteringCaveId = 0;

                i += alteringCaveId;
            }

            return i;
        }
    }

    return HEADER_NONE;
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

static bool8 TryGenerateWildMon(const struct WildPokemonInfo *wildMonInfo, u8 area, u8 flags)
{
    u16 species;
    u8 level;

    u8 requiredType = GetWildMonTypeFromGemItem();
    u8 secondaryType = TYPE_NONE;

    if (area == WILD_AREA_ROCKS)
        secondaryType = TYPE_ROCK;
    else if (CheckForAbilityInfluence(ABILITY_MAGNET_PULL))
        secondaryType = TYPE_STEEL;
    else if (CheckForAbilityInfluence(ABILITY_STATIC))
        secondaryType = TYPE_ELECTRIC;
    else if (CheckForAbilityInfluence(ABILITY_LIGHTNING_ROD))
        secondaryType = TYPE_ELECTRIC;
    else if (CheckForAbilityInfluence(ABILITY_FLASH_FIRE))
        secondaryType = TYPE_FIRE;
    else if (CheckForAbilityInfluence(ABILITY_HARVEST))
        secondaryType = TYPE_GRASS;
    else if (CheckForAbilityInfluence(ABILITY_STORM_DRAIN))
        secondaryType = TYPE_WATER;

    level = ChooseWildMonLevel(wildMonInfo->wildPokemon, area);
    if (flags & WILD_CHECK_REPEL && !IsWildLevelAllowedByRepel(level))
        return FALSE;
    if (gMapHeader.mapLayoutId != LAYOUT_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_WILD_MONS && flags & WILD_CHECK_KEEN_EYE && !IsAbilityAllowingEncounter(level))
        return FALSE;

    species = ChooseWildMonSpecies(requiredType, secondaryType);
    if (species == SPECIES_NONE)
        return FALSE;
    CreateWildMon(species, level);
    return TRUE;
}

static u16 GenerateFishingWildMon(const struct WildPokemonInfo *wildMonInfo, u8 rod)
{
    u8 requiredType = GetWildMonTypeFromGemItem();
    u8 level = ChooseWildMonLevelFishing(rod);
    u16 species = ChooseWildMonSpecies(requiredType, TYPE_WATER);
    // TODO actually handle failure, instead of just defaulting to Magikarp
    if (species == SPECIES_NONE)
        species = SPECIES_MAGIKARP;
    CreateWildMon(species, level);
    return species;
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

bool8 StandardWildEncounter(u16 curMetatileBehavior, u16 prevMetatileBehavior)
{
    u16 headerId;
    struct Roamer *roamer;

    if (sWildEncountersDisabled == TRUE)
        return FALSE;

    headerId = GetCurrentMapWildMonHeaderId();
    if (headerId == HEADER_NONE)
    {
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_WILD_MONS)
        {
            headerId = GetBattlePikeWildMonHeaderId();
            if (prevMetatileBehavior != curMetatileBehavior && !AllowWildCheckOnNewMetatile())
                return FALSE;
            else if (WildEncounterCheck(gBattlePikeWildMonHeaders[headerId].landMonsInfo->encounterRate, FALSE) != TRUE)
                return FALSE;
            else if (TryGenerateWildMon(gBattlePikeWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, WILD_CHECK_KEEN_EYE) != TRUE)
                return FALSE;
            else if (!TryGenerateBattlePikeWildMon(TRUE))
                return FALSE;

            BattleSetup_StartBattlePikeWildBattle();
            return TRUE;
        }
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR)
        {
            headerId = gSaveBlock2Ptr->frontier.curChallengeBattleNum;
            if (prevMetatileBehavior != curMetatileBehavior && !AllowWildCheckOnNewMetatile())
                return FALSE;
            else if (WildEncounterCheck(gBattlePyramidWildMonHeaders[headerId].landMonsInfo->encounterRate, FALSE) != TRUE)
                return FALSE;
            else if (TryGenerateWildMon(gBattlePyramidWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, WILD_CHECK_KEEN_EYE) != TRUE)
                return FALSE;

            GenerateBattlePyramidWildMon();
            BattleSetup_StartWildBattle();
            return TRUE;
        }
    }
    else
    {
        if (MetatileBehavior_IsLandWildEncounter(curMetatileBehavior) == TRUE)
        {
            if (gWildMonHeaders[headerId].landMonsInfo == NULL)
                return FALSE;
            else if (prevMetatileBehavior != curMetatileBehavior && !AllowWildCheckOnNewMetatile())
                return FALSE;
            else if (WildEncounterCheck(gWildMonHeaders[headerId].landMonsInfo->encounterRate, FALSE) != TRUE)
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
                if (TryGenerateWildMon(gWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
                {
                    if (TryDoDoubleWildBattle())
                    {
                        struct Pokemon mon1 = gEnemyParty[0];
                        TryGenerateWildMon(gWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, WILD_CHECK_KEEN_EYE);
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
            else if (gWildMonHeaders[headerId].waterMonsInfo == NULL)
                return FALSE;
            else if (prevMetatileBehavior != curMetatileBehavior && !AllowWildCheckOnNewMetatile())
                return FALSE;
            else if (WildEncounterCheck(gWildMonHeaders[headerId].waterMonsInfo->encounterRate, FALSE) != TRUE)
                return FALSE;

            if (TryStartRoamerEncounter() == TRUE)
            {
                roamer = &gSaveBlock1Ptr->roamer;
                if (!IsWildLevelAllowedByRepel(roamer->level))
                    return FALSE;

                BattleSetup_StartRoamerBattle();
                return TRUE;
            }
            else // try a regular surfing encounter
            {
                // No surfing encounters
                // if (TryGenerateWildMon(gWildMonHeaders[headerId].waterMonsInfo, WILD_AREA_WATER, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
                // {
                //     gIsSurfingEncounter = TRUE;
                //     if (TryDoDoubleWildBattle())
                //     {
                //         struct Pokemon mon1 = gEnemyParty[0];
                //         TryGenerateWildMon(gWildMonHeaders[headerId].waterMonsInfo, WILD_AREA_WATER, WILD_CHECK_KEEN_EYE);
                //         gEnemyParty[1] = mon1;
                //         BattleSetup_StartDoubleWildBattle();
                //     }
                //     else
                //     {
                //         BattleSetup_StartWildBattle();
                //     }
                //     return TRUE;
                // }

                return FALSE;
            }
        }
    }

    return FALSE;
}

void RockSmashWildEncounter(void)
{
    u16 headerId = GetCurrentMapWildMonHeaderId();

    if (headerId != HEADER_NONE)
    {
        const struct WildPokemonInfo *wildPokemonInfo = gWildMonHeaders[headerId].rockSmashMonsInfo;

        if (wildPokemonInfo == NULL)
        {
            gSpecialVar_Result = FALSE;
        }
        else if (WildEncounterCheck(wildPokemonInfo->encounterRate, TRUE) == TRUE
         && TryGenerateWildMon(wildPokemonInfo, WILD_AREA_ROCKS, WILD_CHECK_REPEL | WILD_CHECK_KEEN_EYE) == TRUE)
        {
            BattleSetup_StartWildBattle();
            gSpecialVar_Result = TRUE;
        }
        else
        {
            gSpecialVar_Result = FALSE;
        }
    }
    else
    {
        gSpecialVar_Result = FALSE;
    }
}

bool8 SweetScentWildEncounter(void)
{
    s16 x, y;
    u16 headerId;

    PlayerGetDestCoords(&x, &y);
    headerId = GetCurrentMapWildMonHeaderId();
    if (headerId == HEADER_NONE)
    {
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_WILD_MONS)
        {
            headerId = GetBattlePikeWildMonHeaderId();
            if (TryGenerateWildMon(gBattlePikeWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, 0) != TRUE)
                return FALSE;

            TryGenerateBattlePikeWildMon(FALSE);
            BattleSetup_StartBattlePikeWildBattle();
            return TRUE;
        }
        if (gMapHeader.mapLayoutId == LAYOUT_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR)
        {
            headerId = gSaveBlock2Ptr->frontier.curChallengeBattleNum;
            if (TryGenerateWildMon(gBattlePyramidWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, 0) != TRUE)
                return FALSE;

            GenerateBattlePyramidWildMon();
            BattleSetup_StartWildBattle();
            return TRUE;
        }
    }
    else
    {
        if (MetatileBehavior_IsLandWildEncounter(MapGridGetMetatileBehaviorAt(x, y)) == TRUE)
        {
            if (gWildMonHeaders[headerId].landMonsInfo == NULL)
                return FALSE;

            if (TryStartRoamerEncounter() == TRUE)
            {
                BattleSetup_StartRoamerBattle();
                return TRUE;
            }

            if (DoMassOutbreakEncounterTest() == TRUE)
                SetUpMassOutbreakEncounter(0);
            else
                TryGenerateWildMon(gWildMonHeaders[headerId].landMonsInfo, WILD_AREA_LAND, 0);

            BattleSetup_StartWildBattle();
            return TRUE;
        }
        else if (MetatileBehavior_IsWaterWildEncounter(MapGridGetMetatileBehaviorAt(x, y)) == TRUE)
        {
            if (AreLegendariesInSootopolisPreventingEncounters() == TRUE)
                return FALSE;
            if (gWildMonHeaders[headerId].waterMonsInfo == NULL)
                return FALSE;

            if (TryStartRoamerEncounter() == TRUE)
            {
                BattleSetup_StartRoamerBattle();
                return TRUE;
            }

            // TryGenerateWildMon(gWildMonHeaders[headerId].waterMonsInfo, WILD_AREA_WATER, 0);
            // BattleSetup_StartWildBattle();
            // return TRUE;
            return FALSE;
        }
    }

    return FALSE;
}

bool8 DoesCurrentMapHaveFishingMons(void)
{
    u16 headerId = GetCurrentMapWildMonHeaderId();

    if (headerId != HEADER_NONE && gWildMonHeaders[headerId].fishingMonsInfo != NULL)
        return TRUE;
    else
        return FALSE;
}

void FishingWildEncounter(u8 rod)
{
    u16 species;

    species = GenerateFishingWildMon(gWildMonHeaders[GetCurrentMapWildMonHeaderId()].fishingMonsInfo, rod);
    IncrementGameStat(GAME_STAT_FISHING_CAPTURES);
    SetPokemonAnglerSpecies(species);
    gIsFishingEncounter = TRUE;
    BattleSetup_StartWildBattle();
}

// TODO update these two functions for the new encounter system

u16 GetLocalWildMon(bool8 *isWaterMon)
{
    u16 headerId;
    const struct WildPokemonInfo *landMonsInfo;
    const struct WildPokemonInfo *waterMonsInfo;

    *isWaterMon = FALSE;
    headerId = GetCurrentMapWildMonHeaderId();
    if (headerId == HEADER_NONE)
        return SPECIES_NONE;
    landMonsInfo = gWildMonHeaders[headerId].landMonsInfo;
    waterMonsInfo = gWildMonHeaders[headerId].waterMonsInfo;
    // Neither
    if (landMonsInfo == NULL && waterMonsInfo == NULL)
        return SPECIES_NONE;
    // Land Pokemon
    else if (landMonsInfo != NULL && waterMonsInfo == NULL)
        return landMonsInfo->wildPokemon[0].species;
    // Water Pokemon
    else if (landMonsInfo == NULL && waterMonsInfo != NULL)
    {
        *isWaterMon = TRUE;
        return waterMonsInfo->wildPokemon[0].species;
    }
    // Either land or water Pokemon
    if ((Random() % 100) < 80)
    {
        return landMonsInfo->wildPokemon[0].species;
    }
    else
    {
        *isWaterMon = TRUE;
        return waterMonsInfo->wildPokemon[0].species;
    }
}

u16 GetLocalWaterMon(void)
{
    u16 headerId = GetCurrentMapWildMonHeaderId();

    if (headerId != HEADER_NONE)
    {
        const struct WildPokemonInfo *waterMonsInfo = gWildMonHeaders[headerId].waterMonsInfo;

        if (waterMonsInfo)
            return waterMonsInfo->wildPokemon[0].species;
    }
    return SPECIES_NONE;
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

#include "data.h"

static u8 GetMaxLevelOfSpeciesInWildTable(const struct WildPokemon *wildMon, u16 species, u8 area)
{
    u8 i, maxLevel = 0, numMon = 0;

    switch (area)
    {
    case WILD_AREA_LAND:
        numMon = LAND_WILD_COUNT;
        break;
    case WILD_AREA_WATER:
        numMon = WATER_WILD_COUNT;
        break;
    case WILD_AREA_ROCKS:
        numMon = ROCK_WILD_COUNT;
        break;
    }

    for (i = 0; i < numMon; i++)
    {
        if (wildMon[i].species == species && wildMon[i].maxLevel > maxLevel)
            maxLevel = wildMon[i].maxLevel;
    }

    return maxLevel;
}

static bool8 CheckForAbilityInfluence(u16 ability)
{
    if (GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
        return FALSE;
    else if (GetMonAbility(&gPlayerParty[0]) != ability)
        return FALSE;
    else if (Random() % 2 != 0)
        return FALSE;

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
