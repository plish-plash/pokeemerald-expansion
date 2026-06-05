#ifndef GUARD_WILD_ENCOUNTER_H
#define GUARD_WILD_ENCOUNTER_H

#include "rtc.h"
#include "constants/wild_encounter.h"
#include "wild_encounter_ow.h"

#define HEADER_NONE 0xFFFF

struct MapHabitatData
{
    u8 mapGroup;
    u8 mapNum;
    u8 biome;
    u8 levelMin;
    u8 levelMax;
};

extern const struct MapHabitatData gMapHabitat[103];

extern u8 gEncounterArea;
extern u8 gChainFishingDexNavStreak;

u8 ChooseWildMonLevel(u8 area, u8 min, u8 max);
void DisableWildEncounters(bool8 disabled);
bool8 StandardWildEncounter(u16 currMetaTileBehavior, u16 previousMetaTileBehavior, bool8 checkRate);
bool8 HabitatWildEncounter(u8 area, u32 encounterRate);
bool8 SweetScentWildEncounter(void);
bool8 FishingWildEncounter(u8 rod);
u16 GetLocalWildMon(bool8 *isWaterMon);
u16 GetLocalWaterMon(void);
bool8 UpdateRepelCounter(void);
bool8 IsWildLevelAllowedByRepel(u8 wildLevel);
bool8 IsAbilityAllowingEncounter(u8 level);
bool8 TryDoDoubleWildBattle(void);
bool8 StandardWildEncounter_Debug(void);
u32 CalculateChainFishingShinyRolls(void);
void CreateWildMon(enum Species species, u8 level);
u16 GetMapHabitatIndex();
bool8 TryGenerateWildMon(u8 area, u8 flags);
bool8 SetUpMassOutbreakEncounter(u8 flags);
bool8 DoMassOutbreakEncounterTest(void);
bool8 AreLegendariesInSootopolisPreventingEncounters(void);
bool32 MapHasNoEncounterData(void);

#endif // GUARD_WILD_ENCOUNTER_H
