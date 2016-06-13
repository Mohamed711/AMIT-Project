
#ifndef RTC_H_
#define RTC_H_

#include "../StdTypes.h"


void RTC_Init();

u8 RTC_getHours();
u8 RTC_getSeconds();
u8 RTC_getMinutes();
u8 RTC_getDay();
u8 RTC_getDate();
u8 RTC_getMonth();
u8 RTC_getYear();


#endif /* RTC_H_ */