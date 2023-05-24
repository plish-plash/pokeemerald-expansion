#ifndef GUARD_DAY_NIGHT_H
#define GUARD_DAY_NIGHT_H

#define PALOVER_LIST_TERM 0xFF

struct PaletteOverride
{
    u8 dnOverride;
    u8 slot;
    const void *palette;
};

extern EWRAM_DATA u16 gPlttBufferPreDN[];
extern EWRAM_DATA const struct PaletteOverride *gPaletteOverrides[];

u8 GetCurrentTimeOfDay(void);
u8 GetTimeOfDay(s8 hours);
void LoadCompressedPaletteDayNight(const void *src, u16 offset, u16 size);
void LoadPaletteDayNight(const void *src, u16 offset, u16 size);
void ProcessDayNight(void);
void DoLoadSpritePaletteDayNight(const u16 *src, u16 paletteOffset);

#endif // GUARD_DAY_NIGHT_H