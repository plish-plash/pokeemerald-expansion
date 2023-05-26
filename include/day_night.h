#ifndef GUARD_DAY_NIGHT_H
#define GUARD_DAY_NIGHT_H

extern EWRAM_DATA u16 gPlttBufferPreDN[];

void LoadCompressedPaletteDayNight(const void *src, u16 offset, u16 size);
void LoadPaletteDayNight(const void *src, u16 offset, u16 size);
void ProcessDayNight(void);
void DoLoadSpritePaletteDayNight(const u16 *src, u16 paletteOffset);

#endif // GUARD_DAY_NIGHT_H