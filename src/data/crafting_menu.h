#include "crafting.h"

static const u32 sMenuTiles[] = INCBIN_U32("graphics/crafting/menu.4bpp.lz");
static const u32 sMenuTilemap[] = INCBIN_U32("graphics/crafting/menu.bin.lz");
static const u16 sMenuPalette[] = INCBIN_U16("graphics/crafting/menu.gbapal");

struct CraftingMenuTemplate
{
    const u32 *tiles;
    const u32 *tilemap;
    const u16 *palette;
    const u8 itemX;
    const u8 itemY;
    const u8 itemRowHeight;
    const u8 outputY;
};

static const struct CraftingMenuTemplate sCraftingMenuTemplate =
{
    .tiles = sMenuTiles,
    .tilemap = sMenuTilemap,
    .palette = sMenuPalette,
    .itemX = 80 + 16 + 4,
    .itemY = 16 + 4,
    .itemRowHeight = 24,
    .outputY = 80 + 32 - 2,
};

static const u8 sRecipeCategoryTexts[NUM_RECIPE_CATEGORIES][16] =
{
    [RECIPE_CATEGORY_POKEBALLS] = _("POKé BALLS"),
    [RECIPE_CATEGORY_MEDICINE] = _("MEDICINE"),
};
