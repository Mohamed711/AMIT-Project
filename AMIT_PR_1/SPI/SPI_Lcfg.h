#ifndef SPI_LCFG_H_
#define SPI_LCFG_H_

#include "../StdTypes.h"
#include "SPI_CFG.h"

typedef struct
{
	u32 u32TempFreq;
	u8 u8RegVal;
}CLK_Rate;

typedef struct  
{
	u32 u32MaxFreq;
	u8 u8Mode;
	u8 u8DataOrder;
}SPI_ConfigType;

extern const SPI_ConfigType SPI_InitConfig;
extern const CLK_Rate clk[PRESCALAR_NUM];

#endif /* SPI_LCFG_H_ */