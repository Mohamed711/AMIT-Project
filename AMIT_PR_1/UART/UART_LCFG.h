
#ifndef UART_LCFG_H_
#define UART_LCFG_H_

#include "../StdTypes.h"
#include "UART_CFG.h"

typedef struct  
{
	u32 u32BaudRate;
	u8 u8CharSize;
	u8 u8Parity;
	u8 u8StopBit;
	
}UART_CfgType;

extern const UART_CfgType UART_CfgData;

#endif /* UART_LCFG_H_ */