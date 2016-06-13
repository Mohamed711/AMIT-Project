
#include "KEYPAD_Lcfg.h"
#include "../DIO/DIO.h"

KPD_ConfigType KPD_ConfigData[MAX_KPD_NUM] =
{
{
// rows
	{
		{	
			PD,
			0x10
		},
		{
			PD,
			0x20
		},
		{
			PD,
			0x40
		},
		{
			PD,
			0x80
		}
	},
// columns
	{
		{
			PD,
			0x08
		},
		{
			PD,
			0x04
		},
		{
			PC,
			0x80
		}
	}
}
};


u8 KPD_Map[ROW_NUM][COLUMN_NUM] = 
{
	{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'},
	{'*','0','#'}
};