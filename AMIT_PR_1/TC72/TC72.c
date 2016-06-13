
#include "TC72.h"
#include "../SPI/SPI.h"
#include "../DIO/DIO.h"
#include "TC72_Lcfg.h"

static u8 Read_Or_Write(u8 u8Address)
{
	u8 val;
	DIO_WritePort(TC72_ConfigData.TC72_CE_Port,0xFF,TC72_ConfigData.TC72_CE_Mask);
	SPI_u8TransfereByte(u8Address);
	val = SPI_u8TransfereByte(0x00);
	DIO_WritePort(TC72_ConfigData.TC72_CE_Port,0x00,TC72_ConfigData.TC72_CE_Mask);
	return val;
}

void TC72_Init(u8 u8Mode)
{
	SPI_vidInit();
	DIO_InitPortDirection(TC72_ConfigData.TC72_CE_Port,0xFF,TC72_ConfigData.TC72_CE_Mask);
	if (u8Mode == TC72_MODE_ONE_SHOT)
	{
		Read_Or_Write(0x80);
		Read_Or_Write(0x15);
	}
	else if (u8Mode == TC72_MODE_CONT)
	{
		Read_Or_Write(0x80);
		Read_Or_Write(0x04);
	}
}

u16 TC72_TempRead()
{
	u16 RetVal = 0x0000;
	u16 temp;
	temp = Read_Or_Write(0x02);
	RetVal |= (temp << 8);
	temp = Read_Or_Write(0x01);
	RetVal |= temp;
	return RetVal;
}

float TC72_floatTempRead()
{
	u16 val;
	s8 val1;
	float RetVal;
	val = TC72_TempRead();
	val1 = (val&0xFF00)>>8;
	RetVal = val1;
	if ((val&0x0080) != 0)
	{
		RetVal += 0.5;
	}
	else if ((val&0x0040) != 0)
	{
		RetVal += 0.25;
	}
	else if ((val&0x00C0) != 0)
	{
		RetVal += 0.75;
	}
	return RetVal;
}