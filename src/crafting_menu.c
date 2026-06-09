#include "crafting.h"

#include "gba/types.h"
#include "gba/defines.h"
#include "global.h"
#include "main.h"
#include "bg.h"
#include "text_window.h"
#include "window.h"
#include "constants/characters.h"
#include "palette.h"
#include "task.h"
#include "overworld.h"
#include "malloc.h"
#include "gba/macro.h"
#include "list_menu.h"
#include "menu_helpers.h"
#include "menu.h"
#include "malloc.h"
#include "scanline_effect.h"
#include "sprite.h"
#include "constants/rgb.h"
#include "decompress.h"
#include "constants/songs.h"
#include "sound.h"
#include "strings.h"
#include "string_util.h"
#include "international_string_util.h"
#include "pokemon_icon.h"
#include "graphics.h"
#include "data.h"
#include "pokedex.h"
#include "gpu_regs.h"
#include "item_icon.h"
#include "item.h"
#include "script.h"

#include "data/crafting_menu.h"

struct CraftingMenuState
{
    MainCallback savedCallback;
    u8 loadState;
    s16 craftQuantity;
    u16 craftQuantityMax;
    u8 listTaskid;
    bool8 listIsInitialized;
    u8 itemSprites[4];
    u16 itemsAdded[4];
    u8 numItemsAdded;
    enum Recipe currentRecipe;
    u8 recipeScrollPositions[NUM_RECIPE_CATEGORIES];
    struct ListMenuItem listBuffer[20];
    struct ListMenuTemplate list;
    u8 messageWindowIds[2];
    u8 categorySwitchArrowsTask;
    u16 categorySwitchArrowPos;
};

enum WindowIds
{
    WIN_LIST_HEADER,
    WIN_LIST_CATEGORY,
    WIN_LIST,
    WIN_RECIPE,
};

enum MessageWindowIds
{
    WIN_MESSAGE,
    WIN_MESSAGE_QUANTITY,
};

static EWRAM_DATA struct CraftingMenuState *sCraftingMenuState = NULL;
static EWRAM_DATA u8 *sBg2TilemapBuffer = NULL;
EWRAM_DATA u16 gSavedListScrollOffset = 0;
EWRAM_DATA u16 gSavedListSelectedRow = 0;
EWRAM_DATA enum RecipeCategory gRecipeCategory = RECIPE_CATEGORY_POKEBALLS;

static const struct BgTemplate sBgTemplates_CraftingMenu[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
    {
        .bg = 2,
        .charBaseIndex = 3,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0,
    },
};

#define HEADER_WIDTH    10
#define HEADER_HEIGHT   2
#define CATEGORY_WIDTH  10
#define CATEGORY_HEIGHT 2
#define LIST_WIDTH      10
#define LIST_HEIGHT     16

#define HEADER_SIZE     HEADER_WIDTH * HEADER_HEIGHT
#define CATEGORY_SIZE   CATEGORY_WIDTH * CATEGORY_HEIGHT
#define LIST_SIZE       LIST_WIDTH * LIST_HEIGHT

#define HEADER_BASEBLOCK        0x27
#define CATEGORY_BASEBLOCK      0x27
#define LIST_BASEBLOCK          HEADER_BASEBLOCK + HEADER_SIZE
#define RECIPE_BASEBLOCK        LIST_BASEBLOCK + LIST_SIZE

static const struct WindowTemplate sDefaultCraftingWindows[] =
{
    [WIN_LIST_HEADER] =
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = HEADER_WIDTH,
        .height = HEADER_HEIGHT,
        .paletteNum = 1,
        .baseBlock = HEADER_BASEBLOCK
    },
    [WIN_LIST_CATEGORY] =
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 2,
        .width = CATEGORY_WIDTH,
        .height = CATEGORY_HEIGHT,
        .paletteNum = 1,
        .baseBlock = CATEGORY_BASEBLOCK
    },
    [WIN_LIST] =
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 2,
        .width = LIST_WIDTH,
        .height = LIST_HEIGHT,
        .paletteNum = 1,
        .baseBlock = LIST_BASEBLOCK
    },
    [WIN_RECIPE] =
    {
        .bg = 0,
        .tilemapLeft = LIST_WIDTH + 2,
        .tilemapTop = 2,
        .width = 30 - (LIST_WIDTH + 2),
        .height = LIST_HEIGHT,
        .paletteNum = 1,
        .baseBlock = RECIPE_BASEBLOCK
    },
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sMessageCraftingWindows[] =
{
    [WIN_MESSAGE] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x21F,
    },
    [WIN_MESSAGE_QUANTITY] = {
        .bg = 1,
        .tilemapLeft = 24,
        .tilemapTop = 11,
        .width = 5,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x21F + 0x6C,
    },
};

static const u8 sFontColorTable[][3] =
{
    [0] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY},
    [1] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE, TEXT_COLOR_RED},
};

static void CraftingMenu_SetupCB(void);
static void CraftingMenu_MainCB(void);
static void CraftingMenu_VBlankCB(void);

static void Task_WaitFadeIn(u8 taskId);
static void Task_MainInput(u8 taskId);
static void Task_WaitFadeAndBail(u8 taskId);
static void Task_WaitFadeAndExitGracefully(u8 taskId);

void CraftingMenu_Init(MainCallback callback);
static bool8 CraftingMenu_InitBgs(void);
static void CraftingMenu_FadeAndBail(void);
static bool8 CraftingMenu_LoadGraphics(void);
static void CraftingMenu_InitWindows(void);
static void CraftingMenu_PrintListCategory(void);
static void CraftingMenu_AddIngredientSprite(u16 itemId, u8 id);
static void CraftingMenu_RemoveLastItem(void);
static void CraftingMenu_FreeResources(void);
static void CraftingMenu_AddItem(u16 item);
static void CraftingMenu_SelectRecipe(void);
static void CraftingMenu_CraftRecipe(u8 taskId);

static bool32 CraftingMenu_SpriteIsUsedMultipleTimes(u16 item);
static u32 CraftingMenu_JustifyCenter(const u8 *input, u32 width, u8 fontId);

static void CraftingMenu_InitScrollList(void);
static void CraftingMenu_BuildListRecipes(void);

static void CreateCategorySwitchArrowPair(void);
static void DestroyCategorySwitchArrowPair(void);
static void DisplayMessage(u8 taskId, const u8 *str);
static void AskQuantityThenCraft(u8 taskId, const u8 *str);
u8 ReformatItemDescription(enum Item item, u8 *dest, u8 maxChars); // from overworld.c

static const u8 sText_IngredientCount[] = _("×{STR_VAR_1}  /{STR_VAR_2}");
static const u8 sText_MissingItems[] = _("You do not have the items\nneeded for this recipe.");
static const u8 sText_CraftHowManyVar1[] = _("Craft how many {STR_VAR_1}?");
static const u8 sText_PlayerCrafted[] = _("{PLAYER} crafted {STR_VAR_2} {STR_VAR_1}.");

static const struct ListMenuTemplate sRecipeListMenu =
{
    .items = NULL,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = 0,
    .maxShowed = 8,
    .windowId = WIN_LIST,
    .header_X = 0,
    .item_X = 10,
    .cursor_X = 2,
    .upText_Y = 1,
    .fillValue = TEXT_COLOR_TRANSPARENT,
    .cursorPal = TEXT_COLOR_WHITE,
    .cursorShadowPal = TEXT_COLOR_LIGHT_GRAY,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = FONT_NARROW,
    .cursorKind = CURSOR_BLACK_ARROW,
};

static const struct ScrollArrowsTemplate sBagScrollArrowsTemplate = {
    .firstArrowType = SCROLL_ARROW_LEFT,
    .firstX = 8,
    .firstY = 8,
    .secondArrowType = SCROLL_ARROW_RIGHT,
    .secondX = 64 + 8,
    .secondY = 8,
    .fullyUpThreshold = -1,
    .fullyDownThreshold = -1,
    .tileTag = 111,
    .palTag = 111,
    .palNum = 0,
};

void Task_OpenCraftingMenu(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        CraftingMenu_Init(CB2_ReturnToFieldWithOpenMenu);
        DestroyTask(taskId);
    }
}

void OpenCraftingMenu_FromScript(struct ScriptContext *ctx)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        CraftingMenu_Init(CB2_ReturnToField);
    }
}

void CraftingMenu_Init(MainCallback callback)
{
    sCraftingMenuState = AllocZeroed(sizeof(struct CraftingMenuState));
    if (sCraftingMenuState == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sCraftingMenuState->currentRecipe = RECIPE_NONE;
    sCraftingMenuState->craftQuantity = 1;
    sCraftingMenuState->loadState = 0;
    sCraftingMenuState->listIsInitialized = FALSE;
    sCraftingMenuState->savedCallback = callback;
    memset(sCraftingMenuState->messageWindowIds, WINDOW_NONE, sizeof(sCraftingMenuState->messageWindowIds));
    sCraftingMenuState->categorySwitchArrowsTask = TASK_NONE;
    sCraftingMenuState->categorySwitchArrowPos = 0;

    SetMainCallback2(CraftingMenu_SetupCB);
}

static void CraftingMenu_SetupCB(void)
{
    switch (gMain.state)
    {
    case 0:
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
            sCraftingMenuState->loadState = 0;
            gMain.state++;
        }
        else
        {
            CraftingMenu_FadeAndBail();
            return;
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
        sCraftingMenuState->numItemsAdded = 0;
        CraftingMenu_InitScrollList();
        CraftingMenu_PrintListCategory();
        CreateCategorySwitchArrowPair();
        if (sCraftingMenuState->listIsInitialized)
        {
            u16 index;
            ListMenuGetCurrentItemArrayId(sCraftingMenuState->listTaskid, &index);
            sCraftingMenuState->currentRecipe = sCraftingMenuState->listBuffer[index].id;
            CraftingMenu_SelectRecipe();
        }

        CreateTask(Task_WaitFadeIn, 0);
        gMain.state++;
        break;
    case 6:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    case 7:
        SetVBlankCallback(CraftingMenu_VBlankCB);
        SetMainCallback2(CraftingMenu_MainCB);
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

static void Task_WaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_MainInput;
}

static void Task_MainInput(u8 taskId)
{
    u8 LRKeys;
    s32 recipe = RECIPE_NONE;
    if (sCraftingMenuState->listIsInitialized)
    {
        recipe = ListMenu_ProcessInput(sCraftingMenuState->listTaskid);
        if (recipe == LIST_NOTHING_CHOSEN)
        {
            u16 index;
            ListMenuGetCurrentItemArrayId(sCraftingMenuState->listTaskid, &index);
            recipe = sCraftingMenuState->listBuffer[index].id;
            if (sCraftingMenuState->currentRecipe != recipe)
            {
                sCraftingMenuState->currentRecipe = recipe;
                CraftingMenu_SelectRecipe();
            }
        }
        else if (recipe == LIST_CANCEL)
        {
            PlaySE(SE_SELECT);
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            gTasks[taskId].func = Task_WaitFadeAndExitGracefully;
        }
        else if (recipe >= 0)
        {
            sCraftingMenuState->currentRecipe = recipe;
            CraftingMenu_CraftRecipe(taskId);
        }
    }
    else
    {
        if (sCraftingMenuState->currentRecipe != recipe)
        {
            sCraftingMenuState->currentRecipe = recipe;
            CraftingMenu_SelectRecipe();
        }
        if (JOY_NEW(B_BUTTON))
        {
            PlaySE(SE_SELECT);
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            gTasks[taskId].func = Task_WaitFadeAndExitGracefully;
        }
    }

    LRKeys = GetLRKeysPressed();
    if (JOY_NEW(DPAD_RIGHT) || LRKeys == MENU_R_PRESSED)
    {
        PlaySE(SE_SELECT);
        if (gRecipeCategory != NUM_RECIPE_CATEGORIES - 1)
            gRecipeCategory++;
        else
            gRecipeCategory = 0;

        CraftingMenu_InitScrollList();
        CraftingMenu_PrintListCategory();
    }
    if (JOY_NEW(DPAD_LEFT) || LRKeys == MENU_L_PRESSED)
    {
        PlaySE(SE_SELECT);
        if (gRecipeCategory != 0)
            gRecipeCategory--;
        else
            gRecipeCategory = NUM_RECIPE_CATEGORIES - 1;

        CraftingMenu_InitScrollList();
        CraftingMenu_PrintListCategory();
    }
}

static void Task_WaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sCraftingMenuState->savedCallback);
        CraftingMenu_FreeResources();
        DestroyTask(taskId);
    }
}

static void Task_WaitFadeAndExitGracefully(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sCraftingMenuState->savedCallback);
        CraftingMenu_FreeResources();
        DestroyTask(taskId);
    }
}

static bool8 CraftingMenu_InitBgs(void)
{
    const u32 TILEMAP_BUFFER_SIZE = (1024 * 2);

    sBg2TilemapBuffer = AllocZeroed(TILEMAP_BUFFER_SIZE);
    if (sBg2TilemapBuffer == NULL)
        return FALSE;

    ResetVramOamAndBgCntRegs();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBgTemplates_CraftingMenu, ARRAY_COUNT(sBgTemplates_CraftingMenu));
    SetBgTilemapBuffer(2, sBg2TilemapBuffer);
    ResetAllBgsCoordinates();
    ScheduleBgCopyTilemapToVram(2);

    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);

    return TRUE;
}

static void CraftingMenu_FadeAndBail(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_WaitFadeAndBail, 0);

    SetVBlankCallback(CraftingMenu_VBlankCB);
    SetMainCallback2(CraftingMenu_MainCB);
}

static bool8 CraftingMenu_LoadGraphics(void)
{
    switch (sCraftingMenuState->loadState)
    {
    case 0:
        ResetTempTileDataBuffers();

        DecompressAndCopyTileDataToVram(2, sCraftingMenuTemplate.tiles, 0, 0, 0);
        sCraftingMenuState->loadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            DecompressDataWithHeaderWram(sCraftingMenuTemplate.tilemap, sBg2TilemapBuffer);
            sCraftingMenuState->loadState++;
        }
        break;
    case 2:
        LoadPalette(sCraftingMenuTemplate.palette, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
        LoadPalette(gBagScreenMale_Pal + (PLTT_SIZE_4BPP / 2), BG_PLTT_ID(1), PLTT_SIZE_4BPP);
        sCraftingMenuState->loadState++;
    default:
        sCraftingMenuState->loadState = 0;
        return TRUE;
    }
    return FALSE;
}

static void CraftingMenu_InitWindows(void)
{
    InitWindows(sDefaultCraftingWindows);

    DeactivateAllTextPrinters();
    LoadUserWindowBorderGfx(0, 1, BG_PLTT_ID(14));
    LoadMessageBoxGfx(0, 10, BG_PLTT_ID(13));
    ListMenuLoadStdPalAt(BG_PLTT_ID(12), 1);
    LoadPalette(&gStandardMenuPalette, BG_PLTT_ID(15), PLTT_SIZE_4BPP);

    FillWindowPixelBuffer(WIN_LIST_HEADER, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    FillWindowPixelBuffer(WIN_LIST, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    FillWindowPixelBuffer(WIN_RECIPE, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    PutWindowTilemap(WIN_LIST_HEADER);
    PutWindowTilemap(WIN_LIST);
    PutWindowTilemap(WIN_RECIPE);

    ScheduleBgCopyTilemapToVram(0);
    ScheduleBgCopyTilemapToVram(1);
}

static void CreateCategorySwitchArrowPair(void)
{
    if (sCraftingMenuState->categorySwitchArrowsTask == TASK_NONE)
        sCraftingMenuState->categorySwitchArrowsTask = AddScrollIndicatorArrowPair(&sBagScrollArrowsTemplate, &sCraftingMenuState->categorySwitchArrowPos);
}

static void DestroyCategorySwitchArrowPair(void)
{
    if (sCraftingMenuState->categorySwitchArrowsTask != TASK_NONE)
    {
        RemoveScrollIndicatorArrowPair(sCraftingMenuState->categorySwitchArrowsTask);
        sCraftingMenuState->categorySwitchArrowsTask = TASK_NONE;
    }
}

static void CraftingMenu_PrintListCategory(void)
{
    u8 fontToUse = FONT_NORMAL;
    FillWindowPixelBuffer(WIN_LIST_HEADER, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    AddTextPrinterParameterized4(WIN_LIST_HEADER,
                                 fontToUse,
                                 CraftingMenu_JustifyCenter(sRecipeCategoryTexts[gRecipeCategory], 80, fontToUse), 0, 0, 0,
                                 sFontColorTable[1],
                                 TEXT_SKIP_DRAW,
                                 sRecipeCategoryTexts[gRecipeCategory]);

    CopyWindowToVram(WIN_LIST_HEADER, COPYWIN_GFX);
}

static void CraftingMenu_PrintRecipe(void)
{
    u8 x = sCraftingMenuTemplate.itemX - (LIST_WIDTH * 8) + 4;
    u8 i;
    FillWindowPixelBuffer(WIN_RECIPE, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    if (sCraftingMenuState->currentRecipe != RECIPE_NONE)
    {
        const struct CraftingRecipe* recipe = &gCraftingRecipes[sCraftingMenuState->currentRecipe];
        for (i = 0; i < MAX_RECIPE_INGREDIENTS; i++)
        {
            u8 y = sCraftingMenuTemplate.itemY + (i * sCraftingMenuTemplate.itemRowHeight) - 16;
            if (recipe->ingredients[i] == ITEM_NONE) break;
            ConvertIntToDecimalStringN(gStringVar1, recipe->ingredientCounts[i], STR_CONV_MODE_RIGHT_ALIGN, 2);
            ConvertIntToDecimalStringN(gStringVar2, CountTotalItemQuantityInBag(recipe->ingredients[i]), STR_CONV_MODE_RIGHT_ALIGN, MAX_ITEM_DIGITS);
            StringExpandPlaceholders(gStringVar4, sText_IngredientCount);
            AddTextPrinterParameterized4(WIN_RECIPE, FONT_NARROW, x, y, 0, 0, sFontColorTable[0], TEXT_SKIP_DRAW, GetItemName(recipe->ingredients[i]));
            AddTextPrinterParameterized4(WIN_RECIPE, FONT_NARROW, x + 80 - 8, y, 0, 0, sFontColorTable[0], TEXT_SKIP_DRAW, gStringVar4);
        }
        ReformatItemDescription(recipe->output, gStringVar4, 20);
        AddTextPrinterParameterized4(WIN_RECIPE, FONT_NORMAL, x - 20, sCraftingMenuTemplate.outputY - 16, 0, 0, sFontColorTable[0], TEXT_SKIP_DRAW, gStringVar4);
    }

    CopyWindowToVram(WIN_RECIPE, COPYWIN_GFX);
}

static void CraftingMenu_FreeResources(void)
{
    DestroyCategorySwitchArrowPair();
    if (sCraftingMenuState != NULL)
    {
        if (sCraftingMenuState->listIsInitialized)
        {
            DestroyListMenuTask(sCraftingMenuState->listTaskid, &gSavedListScrollOffset, &gSavedListSelectedRow);
        }
        Free(sCraftingMenuState);
    }
    if (sBg2TilemapBuffer != NULL)
    {
        Free(sBg2TilemapBuffer);
    }
    FreeAllWindowBuffers();
    ResetSpriteData();
}

static u32 CraftingMenu_JustifyCenter(const u8 *input, u32 width, u8 fontId)
{
    u32 currWidth = GetStringWidth(fontId, input, 0);
    if (currWidth < width)
        return (width - currWidth + 1) >> 1;
    else
        return 0;
}

static void CraftingMenu_AddIngredientSprite(u16 itemId, u8 id)
{
    u8 iconSpriteId = AddItemIconSprite(itemId, itemId, itemId);
    if (iconSpriteId != MAX_SPRITES)
    {
        sCraftingMenuState->itemSprites[id] = iconSpriteId;
        gSprites[iconSpriteId].x2 = sCraftingMenuTemplate.itemX + 12;
        gSprites[iconSpriteId].y2 = sCraftingMenuTemplate.itemY + (id * sCraftingMenuTemplate.itemRowHeight) + 12;
    }
}

static void CraftingMenu_RemoveLastItem(void)
{
    u8 id = sCraftingMenuState->itemSprites[--sCraftingMenuState->numItemsAdded];
    u16 currItem = sCraftingMenuState->itemsAdded[sCraftingMenuState->numItemsAdded];
    sCraftingMenuState->itemsAdded[sCraftingMenuState->numItemsAdded] = 0;
    if (CraftingMenu_SpriteIsUsedMultipleTimes(currItem))
    {
        DestroySprite(&gSprites[id]);
    }
    else
    {
        DestroySprite(&gSprites[id]);
        FreeSpriteTilesByTag(currItem);
        FreeSpritePaletteByTag(currItem);
    }
}

static void CraftingMenu_InitScrollList(void)
{
    if (sCraftingMenuState->listIsInitialized)
    {
        DestroyListMenuTask(sCraftingMenuState->listTaskid, NULL, NULL);
    }
    CraftingMenu_BuildListRecipes();
    if (sCraftingMenuState->list.totalItems > 0)
    {
        sCraftingMenuState->listTaskid = ListMenuInit(&sCraftingMenuState->list, gSavedListScrollOffset, gSavedListSelectedRow);
        sCraftingMenuState->listIsInitialized = TRUE;
    }
    else
    {
        FillWindowPixelBuffer(WIN_LIST, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
        sCraftingMenuState->listIsInitialized = FALSE;
    }
    CopyWindowToVram(WIN_LIST, COPYWIN_FULL);
    gSavedListScrollOffset = 0;
    gSavedListSelectedRow = 0;
}

static void CraftingMenu_AddItem(u16 item)
{
    u32 index = sCraftingMenuState->numItemsAdded;
    CraftingMenu_AddIngredientSprite(item, index);
    sCraftingMenuState->itemsAdded[index] = item;
    sCraftingMenuState->numItemsAdded++;
}

static void CraftingMenu_SelectRecipe(void)
{
    u8 i;
    while (sCraftingMenuState->itemsAdded[0] != 0)
        CraftingMenu_RemoveLastItem();
    if (sCraftingMenuState->currentRecipe != RECIPE_NONE)
    {
        const u16* ingredients = gCraftingRecipes[sCraftingMenuState->currentRecipe].ingredients;
        for (i = 0; i < MAX_RECIPE_INGREDIENTS; i++)
        {
            if (ingredients[i] == ITEM_NONE) break;
            CraftingMenu_AddItem(ingredients[i]);
        }
    }
    CraftingMenu_PrintRecipe();
}

static void CraftingMenu_CraftRecipe(u8 taskId)
{
    u16 maxCrafts = CanCraftRecipe(sCraftingMenuState->currentRecipe);
    if (maxCrafts > 0)
    {
        sCraftingMenuState->craftQuantityMax = maxCrafts;
        sCraftingMenuState->craftQuantity = min(sCraftingMenuState->craftQuantity, sCraftingMenuState->craftQuantityMax);
        CopyItemNameHandlePlural(GetRecipeOutput(sCraftingMenuState->currentRecipe), gStringVar1, 2);
        AskQuantityThenCraft(taskId, sText_CraftHowManyVar1);
        PlaySE(SE_SELECT);
    }
    else
    {
        DisplayMessage(taskId, sText_MissingItems);
        PlaySE(SE_FAILURE);
    }
}

static void CraftingMenu_BuildListRecipes(void)
{
    u32 recipeCount = 0;
    for (enum Recipe recipe = 0; recipe < RECIPE_NONE; recipe++)
    {
        if (IsRecipeUnlocked(recipe) && IsRecipeInCategory(recipe, gRecipeCategory))
        {
            sCraftingMenuState->listBuffer[recipeCount].name = GetRecipeName(recipe);
            sCraftingMenuState->listBuffer[recipeCount].id = recipe;
            recipeCount++;
        }
    }
    sCraftingMenuState->list = sRecipeListMenu;
    sCraftingMenuState->list.items = sCraftingMenuState->listBuffer;
    sCraftingMenuState->list.totalItems = recipeCount;
}

static bool32 CraftingMenu_SpriteIsUsedMultipleTimes(u16 item)
{
    u32 count = 0;
    for (u32 i = 0; i < sCraftingMenuState->numItemsAdded; i++)
        if (sCraftingMenuState->itemsAdded[i] == item)
            count++;
    return count != 0;
}

static u8 CraftingMenu_AddWindow(u8 i)
{
    u8 *windowIdLoc = &sCraftingMenuState->messageWindowIds[i];
    if (*windowIdLoc == WINDOW_NONE)
    {
        *windowIdLoc = AddWindow(&sMessageCraftingWindows[i]);
    }
    return *windowIdLoc;
}

static void CraftingMenu_RemoveWindow(u8 i)
{
    u8 *windowIdLoc = &sCraftingMenuState->messageWindowIds[i];
    if (*windowIdLoc != WINDOW_NONE)
    {
        ClearDialogWindowAndFrameToTransparent(*windowIdLoc, FALSE);
        ClearWindowTilemap(*windowIdLoc);
        RemoveWindow(*windowIdLoc);
        ScheduleBgCopyTilemapToVram(1);
        *windowIdLoc = WINDOW_NONE;
    }
}

static u8 CraftingMenu_AddWindow2(u8 i)
{
    u8 *windowId = &sCraftingMenuState->messageWindowIds[i];
    if (*windowId == WINDOW_NONE)
    {
        *windowId = AddWindow(&sMessageCraftingWindows[i]);
        DrawStdFrameWithCustomTileAndPalette(*windowId, FALSE, 1, 14);
        ScheduleBgCopyTilemapToVram(1);
    }
    return *windowId;
}

static void CraftingMenu_RemoveWindow2(u8 i)
{
    u8 *windowId = &sCraftingMenuState->messageWindowIds[i];
    if (*windowId != WINDOW_NONE)
    {
        ClearStdWindowAndFrameToTransparent(*windowId, FALSE);
        ClearWindowTilemap(*windowId);
        RemoveWindow(*windowId);
        ScheduleBgCopyTilemapToVram(1);
        *windowId = WINDOW_NONE;
    }
}

static void CloseMessage(u8 taskId)
{
    CreateCategorySwitchArrowPair();
    CraftingMenu_RemoveWindow(WIN_MESSAGE);
    // ScheduleBgCopyTilemapToVram(0);
    gTasks[taskId].func = Task_MainInput;
}

static void PrintItemQuantity(u8 windowId, s16 quantity)
{
    ConvertIntToDecimalStringN(gStringVar1, quantity, STR_CONV_MODE_LEADING_ZEROS, MAX_ITEM_DIGITS);
    StringExpandPlaceholders(gStringVar4, gText_xVar1);
    AddTextPrinterParameterized(windowId, FONT_NORMAL, gStringVar4, GetStringCenterAlignXOffset(FONT_NORMAL, gStringVar4, 0x28), 2, 0, 0);
}

static void HandleMessage(u8 taskId)
{
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        CloseMessage(taskId);
    }
}

static void HandleQuantity(u8 taskId)
{
    if (sCraftingMenuState->messageWindowIds[WIN_MESSAGE_QUANTITY] == WINDOW_NONE)
    {
        PrintItemQuantity(CraftingMenu_AddWindow2(WIN_MESSAGE_QUANTITY), sCraftingMenuState->craftQuantity);
        return;
    }

    if (AdjustQuantityAccordingToDPadInput(&sCraftingMenuState->craftQuantity, sCraftingMenuState->craftQuantityMax) == TRUE)
    {
        PrintItemQuantity(sCraftingMenuState->messageWindowIds[WIN_MESSAGE_QUANTITY], sCraftingMenuState->craftQuantity);
    }
    else if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SUCCESS);
        CraftRecipe(sCraftingMenuState->currentRecipe, sCraftingMenuState->craftQuantity);
        CraftingMenu_RemoveWindow2(WIN_MESSAGE_QUANTITY);
        CraftingMenu_PrintRecipe();

        CopyItemNameHandlePlural(GetRecipeOutput(sCraftingMenuState->currentRecipe), gStringVar1, sCraftingMenuState->craftQuantity);
        ConvertIntToDecimalStringN(gStringVar2, sCraftingMenuState->craftQuantity, STR_CONV_MODE_LEFT_ALIGN, MAX_ITEM_DIGITS);
        DisplayMessageAndContinueTask(taskId, sCraftingMenuState->messageWindowIds[WIN_MESSAGE], 10, 13, FONT_NORMAL, GetPlayerTextSpeedDelay(), sText_PlayerCrafted, HandleMessage);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        CraftingMenu_RemoveWindow2(WIN_MESSAGE_QUANTITY);
        CloseMessage(taskId);
    }
}

static void DisplayMessage(u8 taskId, const u8 *str)
{
    u8 windowId;
    DestroyCategorySwitchArrowPair();
    windowId = CraftingMenu_AddWindow(WIN_MESSAGE);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
    DisplayMessageAndContinueTask(taskId, windowId, 10, 13, FONT_NORMAL, GetPlayerTextSpeedDelay(), str, HandleMessage);
    ScheduleBgCopyTilemapToVram(1);
}

static void AskQuantityThenCraft(u8 taskId, const u8 *str)
{
    u8 windowId;
    DestroyCategorySwitchArrowPair();
    windowId = CraftingMenu_AddWindow(WIN_MESSAGE);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
    DisplayMessageAndContinueTask(taskId, windowId, 10, 13, FONT_NORMAL, GetPlayerTextSpeedDelay(), str, HandleQuantity);
    ScheduleBgCopyTilemapToVram(1);
}
