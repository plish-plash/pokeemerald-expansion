#include "global.h"
#include "day_night.h"
#include "decompress.h"
#include "event_data.h"
#include "field_tasks.h"
#include "field_weather.h"
#include "overworld.h"
#include "palette.h"
#include "rtc.h"
#include "constants/day_night.h"
#include "constants/region_map_sections.h"
#include "constants/rgb.h"

#define TINT_MORNING Q_8_8(0.7), Q_8_8(0.7), Q_8_8(0.9)
#define TINT_DAY Q_8_8(1.0), Q_8_8(1.0), Q_8_8(1.0)
#define TINT_NIGHT Q_8_8(0.6), Q_8_8(0.6), Q_8_8(0.92)

EWRAM_DATA u16 gPlttBufferPreDN[PLTT_BUFFER_SIZE] = {0};
EWRAM_DATA const struct PaletteOverride *gPaletteOverrides[4] = {NULL};

static EWRAM_DATA struct {
    u8 hours;
    u16 tint[3];
} sDayNight = {0};

static const u16 sTimeOfDayTints[][3] = {
    [0] =   {TINT_NIGHT},
    [1] =   {TINT_NIGHT},
    [2] =   {TINT_NIGHT},
    [3] =   {TINT_NIGHT},
    [4] =   {Q_8_8(0.6), Q_8_8(0.65), Q_8_8(1.0)},
    [5] =   {TINT_MORNING},
    [6] =   {TINT_MORNING},
    [7] =   {TINT_MORNING},
    [8] =   {Q_8_8(0.9), Q_8_8(0.85), Q_8_8(1.0)},
    [9] =   {Q_8_8(1.0), Q_8_8(0.9), Q_8_8(1.0)},
    [10] =  {TINT_DAY},
    [11] =  {TINT_DAY},
    [12] =  {TINT_DAY},
    [13] =  {TINT_DAY},
    [14] =  {TINT_DAY},
    [15] =  {TINT_DAY},
    [16] =  {TINT_DAY},
    [17] =  {Q_8_8(1.0), Q_8_8(0.98), Q_8_8(0.9)},
    [18] =  {Q_8_8(0.9), Q_8_8(0.7), Q_8_8(0.67)},
    [19] =  {Q_8_8(0.75), Q_8_8(0.66), Q_8_8(0.77)},
    [20] =  {Q_8_8(0.7), Q_8_8(0.63), Q_8_8(0.82)},
    [21] =  {TINT_NIGHT},
    [22] =  {TINT_NIGHT},
    [23] =  {TINT_NIGHT},
};

static void LoadPaletteOverrides(void)
{
    u8 i, j;
    const u16* src;
    u16* dest;

    s8 currentOverride = OVERRIDE_PALETTE_DAY;
    if (gLocalTime.hours <= 5 || gLocalTime.hours >= 20)
        currentOverride = OVERRIDE_PALETTE_NIGHT;

    for (i = 0; i < ARRAY_COUNT(gPaletteOverrides); i++)
    {
        const struct PaletteOverride *curr = gPaletteOverrides[i];
        if (curr != NULL)
        {
            while (curr->slot != PALOVER_LIST_TERM && curr->palette != NULL)
            {
                if (curr->dnOverride == currentOverride)
                {
                    for (j = 0, src = curr->palette, dest = gPlttBufferUnfaded + (curr->slot * 16); j < 16; j++, src++, dest++)
                    {
                        if (*src != RGB_BLACK)
                            *dest = *src;
                    }
                }
                curr++;
            }
        }
    }
}

static bool8 ShouldTintOverworld(void)
{
    if (IsMapTypeOutdoors(gMapHeader.mapType))
        return TRUE;

    // more conditions?
    return FALSE;
}

static bool8 CheckTime(void)
{
    const u16 *tint;
    if (sDayNight.hours != gLocalTime.hours)
    {
        sDayNight.hours = gLocalTime.hours;
        tint = sTimeOfDayTints[gLocalTime.hours];
        sDayNight.tint[0] = tint[0];
        sDayNight.tint[1] = tint[1];
        sDayNight.tint[2] = tint[2];
        return TRUE;
    }
    return FALSE;
}

static void TintPaletteForDayNight(u16 offset, u16 size)
{
    if (ShouldTintOverworld())
    {
        CheckTime();
        TintPalette_CustomToneWithCopy(gPlttBufferPreDN + offset, gPlttBufferUnfaded + offset, size / 2, sDayNight.tint[0], sDayNight.tint[1], sDayNight.tint[2], FALSE);
        LoadPaletteOverrides();
    }
    else
    {
        CpuCopy16(gPlttBufferPreDN + offset, gPlttBufferUnfaded + offset, size);
    }
}

void LoadCompressedPaletteDayNight(const void *src, u16 offset, u16 size)
{
    LZDecompressWram(src, gPaletteDecompressionBuffer);
    CpuCopy16(gPaletteDecompressionBuffer, gPlttBufferPreDN + offset, size);
    TintPaletteForDayNight(offset, size);
    CpuCopy16(gPlttBufferUnfaded + offset, gPlttBufferFaded + offset, size);
}

void LoadPaletteDayNight(const void *src, u16 offset, u16 size)
{
    CpuCopy16(src, gPlttBufferPreDN + offset, size);
    TintPaletteForDayNight(offset, size);
    CpuCopy16(gPlttBufferUnfaded + offset, gPlttBufferFaded + offset, size);
}

void ProcessDayNight(void)
{
    if (!ShouldTintOverworld())
        return;
    
    if (CheckTime())
    {
        TintPalette_CustomToneWithCopy(gPlttBufferPreDN, gPlttBufferUnfaded, BG_PLTT_SIZE / 2, sDayNight.tint[0], sDayNight.tint[1], sDayNight.tint[2], TRUE);
        TintPalette_CustomToneWithCopy(gPlttBufferPreDN + (BG_PLTT_SIZE / 2), gPlttBufferUnfaded + (BG_PLTT_SIZE / 2), OBJ_PLTT_SIZE / 2, sDayNight.tint[0], sDayNight.tint[1], sDayNight.tint[2], TRUE);
        LoadPaletteOverrides();
        if (gWeatherPtr->palProcessingState != WEATHER_PAL_STATE_SCREEN_FADING_IN &&
            gWeatherPtr->palProcessingState != WEATHER_PAL_STATE_SCREEN_FADING_OUT)
            CpuCopy16(gPlttBufferUnfaded, gPlttBufferFaded, PLTT_SIZE);
    }
}

void DoLoadSpritePaletteDayNight(const u16 *src, u16 paletteOffset)
{
    LoadPaletteDayNight(src, paletteOffset + 0x100, 32);
}