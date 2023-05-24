#include "global.h"
#include "reset_rtc_screen.h"
#include "event_data.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "rtc.h"
#include "save.h"
#include "sprite.h"
#include "constants/songs.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "scanline_effect.h"
#include "bg.h"
#include "window.h"
#include "gpu_regs.h"
#include "constants/rgb.h"

#define PALTAG_ARROW 0x1000

// Task data for the Task_ResetRtc_* series of tasks, when setting the time on the clock
// Data from these tasks is also used by the cursors and the main task (Task_ResetRtcScreen)
enum {
    DATAIDX_DAYS = 3,
    DATAIDX_HOURS,
    DATAIDX_MINS,
    DATAIDX_SECS,
    DATAIDX_CONFIRM,
};
#define tFinished  data[0]
#define tSetTime   data[1]
#define tSelection data[2]
#define tDays      data[DATAIDX_DAYS]
#define tHours     data[DATAIDX_HOURS]
#define tMinutes   data[DATAIDX_MINS]
#define tSeconds   data[DATAIDX_SECS]
#define tConfirm   data[DATAIDX_CONFIRM]
#define tWindowId  data[8]

enum {
    SELECTION_DAYS = 1,
    SELECTION_HOURS,
    SELECTION_MINS,
    SELECTION_SECS,
    SELECTION_CONFIRM,
    SELECTION_NONE
};

enum {
    WIN_TIME,
    WIN_MSG,
};

struct ResetRtcInputMap
{
    /*0x0*/ u8 dataIndex;
    /*0x2*/ u16 minVal;
    /*0x4*/ u16 maxVal;
    /*0x6*/ u8 left;
    /*0x7*/ u8 right;
    /*0x8*/ u8 unk; // never read
};

static const struct BgTemplate sBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    }
};

static const struct WindowTemplate sWindowTemplates[] =
{
    [WIN_TIME] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 19,
        .height = 9,
        .paletteNum = 15,
        .baseBlock = 0x155
    },
    [WIN_MSG] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0xE9
    },
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sInputTimeWindow = {
    .bg = 0,
    .tilemapLeft = 4,
    .tilemapTop = 9,
    .width = 21,
    .height = 2,
    .paletteNum = 15,
    .baseBlock = 0xBF
};

static const struct ResetRtcInputMap sInputMap[] =
{
    [SELECTION_DAYS - 1] = {
        .dataIndex = DATAIDX_DAYS,
        .minVal = 1,
        .maxVal = 9999,
        .left = 0,
        .right = 2,
        .unk = 0,
    },
    [SELECTION_HOURS - 1] = {
        .dataIndex = DATAIDX_HOURS,
        .minVal = 0,
        .maxVal = 23,
        .left = 1,
        .right = 3,
        .unk = 0,
    },
    [SELECTION_MINS - 1] = {
        .dataIndex = DATAIDX_MINS,
        .minVal = 0,
        .maxVal = 59,
        .left = 2,
        .right = 4,
        .unk = 0,
    },
    [SELECTION_SECS - 1] = {
        .dataIndex = DATAIDX_SECS,
        .minVal = 0,
        .maxVal = 59,
        .left = 3,
        .right = 5,
        .unk = 0,
    },
    [SELECTION_CONFIRM - 1] = {
        .dataIndex = DATAIDX_CONFIRM,
        .minVal = 0,
        .maxVal = 0,
        .left = 4,
        .right = 0,
        .unk = 6,
    },
};

static const struct OamData sOamData_Arrow =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const u8 sArrowDown_Gfx[] = INCBIN_U8("graphics/reset_rtc_screen/arrow_down.4bpp");
static const u8 sArrowRight_Gfx[] = INCBIN_U8("graphics/reset_rtc_screen/arrow_right.4bpp");
static const u16 sArrow_Pal[] = INCBIN_U16("graphics/reset_rtc_screen/arrow.gbapal");

static const struct SpriteFrameImage sPicTable_Arrow[] =
{
    obj_frame_tiles(sArrowDown_Gfx),
    obj_frame_tiles(sArrowRight_Gfx)
};

const struct SpritePalette gSpritePalette_Arrow =
{
    sArrow_Pal, PALTAG_ARROW
};

static const union AnimCmd sAnim_Arrow_Down[] =
{
    ANIMCMD_FRAME(0, 30),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Arrow_Up[] =
{
    ANIMCMD_FRAME(0, 30, .vFlip = TRUE),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_Arrow_Right[] =
{
    ANIMCMD_FRAME(1, 30),
    ANIMCMD_JUMP(0),
};

enum {
    ARROW_DOWN,
    ARROW_UP,
    ARROW_RIGHT,
};

static const union AnimCmd *const sAnims_Arrow[] =
{
    [ARROW_DOWN]  = sAnim_Arrow_Down,
    [ARROW_UP]    = sAnim_Arrow_Up,
    [ARROW_RIGHT] = sAnim_Arrow_Right,
};

const struct SpriteTemplate gSpriteTemplate_Arrow =
{
    .tileTag = TAG_NONE,
    .paletteTag = PALTAG_ARROW,
    .oam = &sOamData_Arrow,
    .anims = sAnims_Arrow,
    .images = sPicTable_Arrow,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};