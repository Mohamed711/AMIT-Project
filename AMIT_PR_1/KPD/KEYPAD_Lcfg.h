
#ifndef KEYPAD_LCFG_H_
#define KEYPAD_LCFG_H_

#include "KEYPAD_Cfg.h"
#include "../StdTypes.h"


typedef struct
{
	u8 Port;
	u8 Mask;
}KPD_Pin;


typedef struct  
{
	KPD_Pin KPD_Row[ROW_NUM];
	KPD_Pin KPD_Column[COLUMN_NUM];
}KPD_ConfigType;

extern KPD_ConfigType KPD_ConfigData[MAX_KPD_NUM];
extern u8 KPD_Map[ROW_NUM][COLUMN_NUM];

#endif /* KEYPAD_LCFG_H_ */