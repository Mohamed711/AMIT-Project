#ifndef TC72_LCFG_H_
#define TC72_LCFG_H_

#include "../StdTypes.h"

typedef struct  
{
	u8 TC72_Clk_Port;
	u8 TC72_Clk_Mask;
	
	u8 TC72_CE_Port;
	u8 TC72_CE_Mask;
	
	u8 TC72_SDO_Port;
	u8 TC72_SDO_Mask;
	
	u8 TC72_SDI_Port;
	u8 TC72_SDI_Mask;
	
}TC72_ConfigType;

extern TC72_ConfigType TC72_ConfigData;

#endif /* TC72_LCFG_H_ */