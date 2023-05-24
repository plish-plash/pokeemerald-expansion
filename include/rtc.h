#ifndef GUARD_RTC_UTIL_H
#define GUARD_RTC_UTIL_H

extern struct Time gLocalTime;

#define CURRENTLY_DAY   (gLocalTime.hours >= 8 && gLocalTime.hours < 18)
#define CURRENTLY_NIGHT (gLocalTime.hours <= 5 || gLocalTime.hours >= 20)
#define CURRENTLY_DUSK  (gLocalTime.hours >= 16 && gLocalTime.hours < 22)

void RtcInit(void);
void RtcCalcLocalTime(void);
void LocalTimeAdvance(void);

#endif // GUARD_RTC_UTIL_H
