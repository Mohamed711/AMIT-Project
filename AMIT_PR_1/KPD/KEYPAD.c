
#include "KEYPAD.h"
#include "KEYPAD_Cfg.h"
#include "KEYPAD_Lcfg.h"
#include "../DIO/DIO.h"
#include <util/delay.h>

void KPD_Init()
{
	u8 LoopIndex;
	u8 InnerLoopIndex;
	u8 val1 , val2;
	
	for (LoopIndex = 0; LoopIndex < MAX_KPD_NUM ; LoopIndex++)
	{
		for (InnerLoopIndex = 0; InnerLoopIndex < ROW_NUM ;InnerLoopIndex++)
		{
			val1 = KPD_ConfigData[LoopIndex].KPD_Row[InnerLoopIndex].Port;
			val2 = KPD_ConfigData[LoopIndex].KPD_Row[InnerLoopIndex].Mask;
			DIO_InitPortDirection(val1,0xFF,val2);
			DIO_WritePort(val1,0xFF,val2);
		}

		for (InnerLoopIndex = 0; InnerLoopIndex < COLUMN_NUM ;InnerLoopIndex++)
		{
			val1 = KPD_ConfigData[LoopIndex].KPD_Column[InnerLoopIndex].Port;
			val2 = KPD_ConfigData[LoopIndex].KPD_Column[InnerLoopIndex].Mask;
			DIO_InitPortDirection(val1,0x00,val2);
			DIO_WritePort(val1,0xFF,val2);
		}
	}
}

u8 KPD_Getkey(u8 KpdID)
{
	u8 LoopIndex;
	u8 InnerLoopIndex;
	u8 RetVal = 0;
	u8 PinVal = 1;
	static u8 prevVal = 0;
	
	for (LoopIndex = 0; LoopIndex < ROW_NUM;LoopIndex++)
	{
		DIO_WritePort(KPD_ConfigData[KpdID].KPD_Row[LoopIndex].Port,0x00,
		KPD_ConfigData[KpdID].KPD_Row[LoopIndex].Mask);

		for (InnerLoopIndex = 0; InnerLoopIndex < COLUMN_NUM ; InnerLoopIndex++)
		{
			PinVal = DIO_ReadPort(KPD_ConfigData[KpdID].KPD_Column[InnerLoopIndex].Port,
				KPD_ConfigData[KpdID].KPD_Column[InnerLoopIndex].Mask);

			if (PinVal == 0)
			{
				RetVal = KPD_Map[LoopIndex][InnerLoopIndex];
				break;
			}
		}

	DIO_WritePort(KPD_ConfigData[KpdID].KPD_Row[LoopIndex].Port,0xFF,
	KPD_ConfigData[KpdID].KPD_Row[LoopIndex].Mask);
	}
	
	if (prevVal == RetVal)
	{
		RetVal = 0;
	}
	else 
	{
		prevVal = RetVal;
	}
	
	return RetVal;
}