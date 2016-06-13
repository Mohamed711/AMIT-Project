
#ifndef LCD_LCFG_H_
#define LCD_LCFG_H_

#include "LCD_Cfg.h"
#include "../StdTypes.h"

typedef struct  
{
	u8 RegisterSelectPort;
	u8 RegisterSelectMask;
	u8 ReadWriteControlPort;
	u8 ReadWriteControlMask;
	u8 EnablePort;
	u8 EnableMask;
	u8 DataPort;
	u8 DataMask;

}LCD_ConfigType;

extern LCD_ConfigType LCD_ConfigData[MAX_LCD_NUM];

#endif /* LCD_LCFG_H_ */