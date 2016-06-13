#ifndef TC72_H_
#define TC72_H_

#include "../StdTypes.h"

#define TC72_MODE_CONT		0x00
#define TC72_MODE_ONE_SHOT	0x01

void TC72_Init(u8 u8Mode);
u16 TC72_TempRead();
float TC72_floatTempRead();

#endif /* TC72_H_ */