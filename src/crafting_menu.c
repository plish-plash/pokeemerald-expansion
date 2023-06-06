#include "global.h"
#include "strings.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "item.h"
#include "item_menu.h"
#include "item_menu_icons.h"
#include "list_menu.h"
#include "item_icon.h"
#include "item_use.h"
#include "international_string_util.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "palette.h"
#include "party_menu.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"
#include "overworld.h"
#include "event_data.h"
#include "crafting.h"
#include "crafting_menu.h"
#include "constants/items.h"
#include "constants/field_weather.h"
#include "constants/songs.h"
#include "constants/rgb.h"

#define TAG_SCROLL_ARROW   2100
 
//==========DEFINES==========//
struct CraftingMenuResources
{
    MainCallback savedCallback;     // determines callback to run when we exit. e.g. where do we want to go after closing the menu
    u8 gfxLoadState;
};

struct ListBuffer1 {
    struct ListMenuItem subBuffers[RECIPES_COUNT];
};

struct ListBuffer2 {
    s8 name[RECIPES_COUNT][ITEM_NAME_LENGTH + 10];
};

enum WindowIds
{
    CRAFTINGWIN_INFO,
    CRAFTINGWIN_RECIPES,
    CRAFTINGWIN_MESSAGE,
};

enum {
    COLORID_NORMAL,      // Item descriptions, quantity in bag, and quantity/price
    COLORID_ITEM_LIST,   // The text in the item list, and the cursor normally
    COLORID_GRAY_CURSOR, // When the cursor has selected an item to purchase
};

//==========EWRAM==========//
static EWRAM_DATA struct CraftingMenuResources *sCraftingMenuDataPtr = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;
static EWRAM_DATA struct ListBuffer1 *sListBuffer1 = 0;
static EWRAM_DATA struct ListBuffer2 *sListBuffer2 = 0;
static EWRAM_DATA u16 sRecipesScrollPosition = 0;
static EWRAM_DATA u16 sRecipesCursorPosition = 0;

//==========STATIC=DEFINES==========//
static void CraftingMenu_RunSetup(void);
static bool8 CraftingMenu_DoGfxSetup(void);
static bool8 CraftingMenu_InitBgs(void);
static void CraftingMenu_FadeAndBail(void);
static bool8 CraftingMenu_LoadGraphics(void);
static void CraftingMenu_InitWindows(void);
static void CraftingMenu_InitRecipeList(u8 taskId);
static void CraftingMenu_AddScrollIndicator(u8 taskId);
static void CraftingMenu_RemoveScrollIndicator(u8 taskId);
static void CraftingRecipesCursorCallback(s32 itemIndex, bool8 onInit, struct ListMenu *list);
static void CraftingRecipesPrintInfo(s32 itemIndex);
static void Task_CraftingMenuWaitFadeIn(u8 taskId);
static void Task_CraftingMenuTryCraft(u8 taskId);
static void Task_CraftingMenuReturnToRecipes(u8 taskId);
static void Task_CraftingMenuMain(u8 taskId);

//==========CONST=DATA==========//
static const struct BgTemplate sCraftingMenuBgTemplates[] =
{
    {
        .bg = 0,    // windows, etc
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 1
    }, 
    {
        .bg = 1,    // this bg loads the UI tilemap
        .charBaseIndex = 3,
        .mapBaseIndex = 29,
        .priority = 2
    },
    {
        .bg = 2,    // this bg loads the UI tilemap
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .priority = 0
    }
};

static const struct WindowTemplate sCraftingMenuWindowTemplates[] = 
{
    [CRAFTINGWIN_INFO] = 
    {
        .bg = 0,            // which bg to print text on
        .tilemapLeft = 14,  // position from left (per 8 pixels)
        .tilemapTop = 2,    // position from top (per 8 pixels)
        .width = 14,        // width (per 8 pixels)
        .height = 16,       // height (per 8 pixels)
        .paletteNum = 15,   // palette index to use for text
        .baseBlock = 30,    // tile start in VRAM
    },
    [CRAFTINGWIN_RECIPES] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 2,
        .width = 12,
        .height = 16,
        .paletteNum = 15,
        .baseBlock = 260,
    },
    [CRAFTINGWIN_MESSAGE] = {
        .bg = 2,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 460,
    },
};

static const struct WindowTemplate sCraftingMenuYesNoWindowTemplate =
{
    .bg = 2,
    .tilemapLeft = 21,
    .tilemapTop = 9,
    .width = 5,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = 570,
};

static const u32 sCraftingMenuTiles[] = INCBIN_U32("graphics/crafting_menu/tiles.4bpp.lz");
static const u32 sCraftingMenuTilemap[] = INCBIN_U32("graphics/crafting_menu/tilemap.bin.lz");
static const u16 sCraftingMenuPalette[] = INCBIN_U16("graphics/crafting_menu/palette.gbapal");

static const u8 sCraftingMenuTextColors[][3] =
{
    [COLORID_NORMAL]      = {1, 2, 3},
    [COLORID_ITEM_LIST]   = {0, 2, 3},
    [COLORID_GRAY_CURSOR] = {0, 3, 2},
};

static const struct ListMenuTemplate sRecipesListTemplate =
{
    .items = NULL,
    .moveCursorFunc = CraftingRecipesCursorCallback,
    .itemPrintFunc = NULL,
    .totalItems = 0,
    .maxShowed = 8,
    .windowId = CRAFTINGWIN_RECIPES,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 0,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = FONT_NARROW,
    .cursorKind = CURSOR_BLACK_ARROW,
};

static const struct YesNoFuncTable sCraftYesNoFuncs =
{
    Task_CraftingMenuTryCraft,
    Task_CraftingMenuReturnToRecipes,
};

//==========FUNCTIONS==========//
// UI loader template
void Task_OpenCraftingMenuFromStartMenu(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        CraftingMenu_Init(CB2_ReturnToFieldWithOpenMenu);
        DestroyTask(taskId);
    }
}

// This is our main initialization function if you want to call the menu from elsewhere
void CraftingMenu_Init(MainCallback callback)
{
    if ((sCraftingMenuDataPtr = AllocZeroed(sizeof(struct CraftingMenuResources))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }
    
    // initialize stuff
    sCraftingMenuDataPtr->gfxLoadState = 0;
    sCraftingMenuDataPtr->savedCallback = callback;
    
    SetMainCallback2(CraftingMenu_RunSetup);
}

static void CraftingMenu_RunSetup(void)
{
    while (1)
    {
        if (CraftingMenu_DoGfxSetup() == TRUE)
            break;
    }
}

static void CraftingMenu_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void CraftingMenu_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static bool8 CraftingMenu_DoGfxSetup(void)
{
    u8 taskId;
    switch (gMain.state)
    {
    case 0:
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000)
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        gMain.state++;
        break;
    case 2:
        if (CraftingMenu_InitBgs())
        {
            sCraftingMenuDataPtr->gfxLoadState = 0;
            gMain.state++;
        }
        else
        {
            CraftingMenu_FadeAndBail();
            return TRUE;
        }
        break;
    case 3:
        if (CraftingMenu_LoadGraphics() == TRUE)
            gMain.state++;
        break;
    case 4:
        CraftingMenu_InitWindows();
        gMain.state++;
        break;
    case 5:
        taskId = CreateTask(Task_CraftingMenuWaitFadeIn, 0);
        CraftingMenu_InitRecipeList(taskId);
        BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
        gMain.state++;
        break;
    case 6:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(CraftingMenu_VBlankCB);
        SetMainCallback2(CraftingMenu_MainCB);
        return TRUE;
    }
    return FALSE;
}

#define try_free(ptr) ({        \
    void ** ptr__ = (void **)&(ptr);   \
    if (*ptr__ != NULL)                \
        Free(*ptr__);                  \
})

static void CraftingMenu_FreeResources(void)
{
    try_free(sCraftingMenuDataPtr);
    try_free(sBg1TilemapBuffer);
    try_free(sListBuffer1);
    try_free(sListBuffer2);
    FreeAllWindowBuffers();
}


static void Task_CraftingMenuWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sCraftingMenuDataPtr->savedCallback);
        CraftingMenu_FreeResources();
        DestroyTask(taskId);
    }
}

static void CraftingMenu_FadeAndBail(void)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_CraftingMenuWaitFadeAndBail, 0);
    SetVBlankCallback(CraftingMenu_VBlankCB);
    SetMainCallback2(CraftingMenu_MainCB);
}

static bool8 CraftingMenu_InitBgs(void)
{
    ResetAllBgsCoordinates();
    sBg1TilemapBuffer = Alloc(0x800);
    if (sBg1TilemapBuffer == NULL)
        return FALSE;
    sListBuffer1 = Alloc(sizeof(*sListBuffer1));
    sListBuffer2 = Alloc(sizeof(*sListBuffer2));
    if (sListBuffer1 == NULL || sListBuffer2 == NULL)
        return FALSE;
    
    memset(sBg1TilemapBuffer, 0, 0x800);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sCraftingMenuBgTemplates, NELEMS(sCraftingMenuBgTemplates));
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    ScheduleBgCopyTilemapToVram(1);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    return TRUE;
}

static bool8 CraftingMenu_LoadGraphics(void)
{
    switch (sCraftingMenuDataPtr->gfxLoadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(1, sCraftingMenuTiles, 0, 0, 0);
        sCraftingMenuDataPtr->gfxLoadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            LZDecompressWram(sCraftingMenuTilemap, sBg1TilemapBuffer);
            sCraftingMenuDataPtr->gfxLoadState++;
        }
        break;
    case 2:
        LoadPalette(sCraftingMenuPalette, 0, 32);
        sCraftingMenuDataPtr->gfxLoadState++;
        break;
    default:
        sCraftingMenuDataPtr->gfxLoadState = 0;
        return TRUE;
    }
    return FALSE;
}

static void CraftingMenu_InitWindows()
{
    u8 i;

    InitWindows(sCraftingMenuWindowTemplates);
    DeactivateAllTextPrinters();
    LoadUserWindowBorderGfx(0, 0x1, BG_PLTT_ID(14));
    LoadMessageBoxGfx(0, 0xA, BG_PLTT_ID(13));
    LoadPalette(gStandardMenuPalette, BG_PLTT_ID(15), PLTT_SIZE_4BPP);

    for (i = 0; i < ARRAY_COUNT(sCraftingMenuWindowTemplates); i++)
        FillWindowPixelBuffer(i, PIXEL_FILL(0));

    PutWindowTilemap(CRAFTINGWIN_RECIPES);
    PutWindowTilemap(CRAFTINGWIN_INFO);
    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(2);
}

static void CraftingMenu_Print(u8 windowId, const u8 *text, u8 x, u8 y, s8 speed, u8 colorSet)
{
    AddTextPrinterParameterized4(windowId, FONT_NORMAL, x, y, 0, 0, sCraftingMenuTextColors[colorSet], speed, text);
}

static void CraftingMenu_InitRecipeList(u8 taskId)
{
    u16 i;
    u16 listIndex;
    s16 *data = gTasks[taskId].data;

    gMultiuseListMenuTemplate = sRecipesListTemplate;
    for (i = 0; i < RECIPES_COUNT; i++)
    {
        if (!IsRecipeUnlocked(i)) continue;
        listIndex = gMultiuseListMenuTemplate.totalItems;
        CopyItemName(gRecipes[i].result, sListBuffer2->name[listIndex]);
        sListBuffer1->subBuffers[listIndex].name = sListBuffer2->name[listIndex];
        sListBuffer1->subBuffers[listIndex].id = i;
        gMultiuseListMenuTemplate.totalItems++;
    }
    gMultiuseListMenuTemplate.items = sListBuffer1->subBuffers;
    gMultiuseListMenuTemplate.maxShowed = min(gMultiuseListMenuTemplate.maxShowed, gMultiuseListMenuTemplate.totalItems);

    data[0] = ListMenuInit(&gMultiuseListMenuTemplate, sRecipesScrollPosition, sRecipesCursorPosition);
    data[1] = TASK_NONE;
    CraftingMenu_AddScrollIndicator(taskId);
}

static void CraftingMenu_AddScrollIndicator(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (data[1] == TASK_NONE && gMultiuseListMenuTemplate.maxShowed < gMultiuseListMenuTemplate.totalItems)
        data[1] = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, 48, 12, 148,
                                                           gMultiuseListMenuTemplate.totalItems - gMultiuseListMenuTemplate.maxShowed,
                                                           TAG_SCROLL_ARROW,
                                                           TAG_SCROLL_ARROW,
                                                           &sRecipesScrollPosition);
}

static void CraftingMenu_RemoveScrollIndicator(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (data[1] != TASK_NONE)
    {
        RemoveScrollIndicatorArrowPair(data[1]);
        data[1] = TASK_NONE;
    }
}

static void CraftingMenu_DisplayMessage(u8 taskId, const u8 *text, TaskFunc callback)
{
    DisplayMessageAndContinueTask(taskId, CRAFTINGWIN_MESSAGE, 0xA, 0xD, FONT_NORMAL, GetPlayerTextSpeedDelay(), text, callback);
    ScheduleBgCopyTilemapToVram(2);
}

static void CraftingRecipesCursorCallback(s32 itemIndex, bool8 onInit, struct ListMenu *list)
{
    if (onInit != TRUE)
        PlaySE(SE_SELECT);
    CraftingRecipesPrintInfo(itemIndex);
}

static void CraftingRecipesPrintInfo(s32 itemIndex)
{
    u8 i;
    u8 y = 1;
    int offset;
    u16 quantityInBag;
    const struct Recipe *recipe = &gRecipes[itemIndex];

    FillWindowPixelBuffer(CRAFTINGWIN_INFO, PIXEL_FILL(0));
    
    for (i = 0; i < MAX_RECIPE_INGREDIENTS; i++)
    {
        if (recipe->ingredients[i] == ITEM_NONE || recipe->ingredientQuantities[i] == 0) break;
        // name
        CopyItemName(recipe->ingredients[i], gStringVar1);
        AddTextPrinterParameterized4(CRAFTINGWIN_INFO, FONT_NARROW, 1, y, 0, 0, sCraftingMenuTextColors[COLORID_ITEM_LIST], TEXT_SKIP_DRAW, gStringVar1);
        // quantity
        ConvertIntToDecimalStringN(gStringVar1, recipe->ingredientQuantities[i], STR_CONV_MODE_RIGHT_ALIGN, BAG_ITEM_CAPACITY_DIGITS);
        StringExpandPlaceholders(gStringVar4, gText_xVar1);
        offset = GetStringRightAlignXOffset(FONT_NARROW, gStringVar4, 111);
        AddTextPrinterParameterized4(CRAFTINGWIN_INFO, FONT_NARROW, offset, y, 0, 0, sCraftingMenuTextColors[COLORID_ITEM_LIST], TEXT_SKIP_DRAW, gStringVar4);
        // number in bag
        y += 0x10;
        quantityInBag = CountTotalItemQuantityInBag(recipe->ingredients[i]);
        ConvertIntToDecimalStringN(gStringVar1, quantityInBag, STR_CONV_MODE_RIGHT_ALIGN, BAG_ITEM_CAPACITY_DIGITS);
        StringExpandPlaceholders(gStringVar4, gText_InBagVar1);
        offset = GetStringRightAlignXOffset(FONT_NARROW, gStringVar4, 111);
        AddTextPrinterParameterized4(CRAFTINGWIN_INFO, FONT_NARROW, offset, y, 0, 0, sCraftingMenuTextColors[COLORID_ITEM_LIST], TEXT_SKIP_DRAW, gStringVar4);
        
        y += 0x10;
    }

    CopyWindowToVram(CRAFTINGWIN_INFO, COPYWIN_GFX);
}

static void CraftingRecipesPrintCursor(u8 scrollIndicatorsTaskId, u8 colorSet)
{
    u8 y = ListMenuGetYCoordForPrintingArrowCursor(scrollIndicatorsTaskId);
    CraftingMenu_Print(CRAFTINGWIN_RECIPES, gText_SelectorArrow2, 0, y, 0, colorSet);
}

static void Task_CraftingMenuWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_CraftingMenuMain;
}

static void Task_CraftingMenuTurnOff(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        CraftingMenu_RemoveScrollIndicator(taskId);
        DestroyListMenuTask(data[0], &sRecipesScrollPosition, &sRecipesCursorPosition);

        SetMainCallback2(sCraftingMenuDataPtr->savedCallback);
        CraftingMenu_FreeResources();
        DestroyTask(taskId);
    }
}

static void Task_CraftingMenuTryCraft(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    const struct Recipe *recipe = &gRecipes[data[2]];
    u8 i;

    if (AddBagItem(recipe->result, 1) == TRUE)
    {
        for (i = 0; i < MAX_RECIPE_INGREDIENTS; i++)
        {
            if (recipe->ingredients[i] == ITEM_NONE || recipe->ingredientQuantities[i] == 0) break;
            RemoveBagItem(recipe->ingredients[i], recipe->ingredientQuantities[i]);
        }
        CraftingMenu_DisplayMessage(taskId, gText_PlayerCreatedVar1, Task_CraftingMenuReturnToRecipes);
    }
    else
    {
        CraftingMenu_DisplayMessage(taskId, gText_NoMoreRoomForThis, Task_CraftingMenuReturnToRecipes);
    }
}

static void Task_CraftingMenuReturnToRecipes(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    ClearDialogWindowAndFrameToTransparent(CRAFTINGWIN_MESSAGE, FALSE);
    RedrawListMenu(data[0]);
    CraftingRecipesPrintCursor(data[0], COLORID_ITEM_LIST);
    ScheduleBgCopyTilemapToVram(2);
    CraftingMenu_AddScrollIndicator(taskId);
    gTasks[taskId].func = Task_CraftingMenuMain;
}

static void Task_CraftingMenuConfirm(u8 taskId)
{
    CreateYesNoMenuWithCallbacks(taskId, &sCraftingMenuYesNoWindowTemplate, 1, 0, 0, 1, 14, &sCraftYesNoFuncs);
}

static void Task_CraftingMenuMain(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    s32 listItemId;

    listItemId = ListMenu_ProcessInput(data[0]);
    ListMenuGetScrollAndRow(data[0], &sRecipesScrollPosition, &sRecipesCursorPosition);
    switch (listItemId)
    {
    case LIST_NOTHING_CHOSEN:
        break;
    case LIST_CANCEL:
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_CraftingMenuTurnOff;
        break;
    default:
        PlaySE(SE_SELECT);
        CraftingMenu_RemoveScrollIndicator(taskId);
        CraftingRecipesPrintCursor(data[0], COLORID_GRAY_CURSOR);
        data[2] = listItemId;
        CopyItemName(gRecipes[listItemId].result, gStringVar1);
        if (GetMaxCraftingCount(listItemId) == 0)
            CraftingMenu_DisplayMessage(taskId, gText_NotEnoughToCraftVar1, Task_CraftingMenuReturnToRecipes);
        else if (!CheckBagHasSpace(gRecipes[listItemId].result, 1))
            CraftingMenu_DisplayMessage(taskId, gText_NoRoomInBag, Task_CraftingMenuReturnToRecipes);
        else
            CraftingMenu_DisplayMessage(taskId, gText_CraftVar1, Task_CraftingMenuConfirm);
        break;
    }
}
