
#include "SPI.h"
#include "../DIO/DIO.h"
#include "SPI_Lcfg.h"
#include "SPI_CFG.h"
#include <avr/interrupt.h>

static volatile u8 u8Data;
static volatile u8 u8DataReceived;

void SPI_vidInit(void)
{
	u8 u8LoopCount;
	
	#if (SPI_MSTR_OR_SLAVE == SPI_MASTER_EN)
		DIO_InitPortDirection(PB,0xFF,0xA0);	// MOSI,MISO,SCK Port direction
	#else
		DIO_InitPortDirection(PB,0xFF,0x40);	// MISO Port direction
	#endif
	
	/*Get the most suitable pre-scalar */
	for(u8LoopCount = 0; u8LoopCount < PRESCALAR_NUM ;u8LoopCount++)
	{
		if(clk[u8LoopCount].u32TempFreq < SPI_InitConfig.u32MaxFreq)
		{
			break;
		}
	}
	
	SPCR_REG = 0X00;
	SPCR_REG |= SPI_MSTR_OR_SLAVE | SPI_EN | SPI_InitConfig.u8Mode | SPI_InitConfig.u8DataOrder|(clk[u8LoopCount].u8RegVal & 0x03);
	SPSR_REG = 0x00;
	SPSR_REG |= (clk[u8LoopCount].u8RegVal >> 2); 
}

u8 SPI_u8TransfereByte(u8 u8Byte)
{
		SPDR_REG = u8Byte;
		while((SPSR_REG&(SPI_INT_FL))== 0x00)
		;
		u8Byte = SPDR_REG;
		return u8Byte;
}

