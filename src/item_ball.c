#include "global.h"
#include "item_ball.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "fieldmap.h"
#include "field_player_avatar.h"
#include "random.h"
#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/map_types.h"
#include "constants/trainer_types.h"

#define ROUTE_ITEM_START  ITEM_LONELY_MINT
#define ROUTE_ITEM_END    ITEM_SERIOUS_MINT
#define CAVE_ITEM         ITEM_TUMBLESTONE
#define METEOR_FALLS_ITEM ITEM_COMET_SHARD

static EWRAM_DATA bool8 sJustTransitionedMaps = FALSE;

static u32 GetItemBallAmountFromTemplate(u32 itemBallId)
{
    u32 amount = gMapHeader.events->objectEvents[itemBallId].movementRangeX;

    if (amount > MAX_BAG_ITEM_CAPACITY)
        return MAX_BAG_ITEM_CAPACITY;

    return (amount == 0) ? 1 : amount;
}

static u32 GetItemBallIdFromTemplate(u32 itemBallId)
{
    enum Item itemId = gMapHeader.events->objectEvents[itemBallId].trainerRange_berryTreeId;

    return (itemId >= ITEMS_COUNT) ? (ITEM_NONE + 1) : itemId;
}

void GetItemBallIdAndAmountFromTemplate(void)
{
    if (IS_LOCALID_ITEM_SPAWN(gSpecialVar_LastTalked))
    {
        gSpecialVar_Result = gObjectEvents[GetObjectEventIdByLocalId(gSpecialVar_LastTalked)].trainerRange_berryTreeId;
        gSpecialVar_0x8009 = 1;
    }
    else
    {
        u32 itemBallId = (gSpecialVar_LastTalked - 1);
        gSpecialVar_Result = GetItemBallIdFromTemplate(itemBallId);
        gSpecialVar_0x8009 = GetItemBallAmountFromTemplate(itemBallId);
    }
}

static void RemoveAllSpawnedItems(void)
{
    for (u32 i = 0; i < OBJECT_EVENTS_COUNT; ++i)
    {
        struct ObjectEvent *obj = &gObjectEvents[i];
        if (IS_LOCALID_ITEM_SPAWN(obj->localId))
        {
            RemoveObjectEvent(obj);
        }
    }
}

void SpawnRandomItemsForCurrentMap(void)
{
    int i;
    int retries = 20;
    u16 mapWidth = gMapHeader.mapLayout->width;
    u16 mapHeight = gMapHeader.mapLayout->height;
    
    enum Item item = CAVE_ITEM;
    u8 numItemsToSpawn = 0;
    if (gMapHeader.mapType == MAP_TYPE_ROUTE)
    {
        numItemsToSpawn = 1;
        item = ROUTE_ITEM_START + (Random() % (ROUTE_ITEM_END - ROUTE_ITEM_START + 1));
    }
    else if (gMapHeader.mapType == MAP_TYPE_UNDERGROUND)
    {
        numItemsToSpawn = min((mapWidth * mapHeight) / 300, 8);
        if (gMapHeader.regionMapSectionId == MAPSEC_METEOR_FALLS)
            item = METEOR_FALLS_ITEM;
    }

    RemoveAllSpawnedItems();

    for (i = 0; i < numItemsToSpawn; i++)
    {
        int x = (Random() % mapWidth) + MAP_OFFSET;
        int y = (Random() % mapHeight) + MAP_OFFSET;

        u8 elevation = MapGridGetElevationAt(x, y);
        if (elevation == ELEVATION_TRANSITION || elevation == ELEVATION_MULTI_LEVEL
         || MapGridGetCollisionAt(x, y)
         || GetObjectEventIdByPosition(x, y, 0) != OBJECT_EVENTS_COUNT)
        {
            if (retries > 0)
            {
                retries--;
                i--;
            }
            continue;
        }
        
        struct ObjectEventTemplate objectEventTemplate = {
            .localId = LOCALID_ITEM_SPAWN_END - i,
            .graphicsId = OBJ_EVENT_GFX_ITEM_SPARKLE,
            .kind = OBJ_KIND_NORMAL,
            .x = x - MAP_OFFSET,
            .y = y - MAP_OFFSET,
            .elevation = 3,
            .movementType = MOVEMENT_TYPE_NONE,
            .movementRangeX = 1,
            .movementRangeY = 1,
            .trainerType = TRAINER_TYPE_NONE,
            .trainerRange_berryTreeId = item,
            .flagId = 0,
        };
        SpawnSpecialObjectEvent(&objectEventTemplate);
    }
}

void TrySpawnRandomItemsForCurrentMap(void)
{
    if (sJustTransitionedMaps)
    {
        SpawnRandomItemsForCurrentMap();
        sJustTransitionedMaps = FALSE;
    }
}

void RandomItemsMapTransition(void)
{
    sJustTransitionedMaps = TRUE;
}