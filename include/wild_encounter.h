#ifndef GUARD_WILD_ENCOUNTER_H
#define GUARD_WILD_ENCOUNTER_H

extern u8 gEncounterArea;

void DisableWildEncounters(bool8 disabled);
bool8 StandardWildEncounter(u16 currMetaTileBehavior, u16 previousMetaTileBehavior, bool8 checkRate);
bool8 HabitatWildEncounter(u8 area, u32 encounterRate);
bool8 SweetScentWildEncounter(void);
void FishingWildEncounter(u8 rod);
u16 GetLocalWildMon(bool8 *isWaterMon);
u16 GetLocalWaterMon(void);
bool8 UpdateRepelCounter(void);
bool8 TryDoDoubleWildBattle(void);

#endif // GUARD_WILD_ENCOUNTER_H
