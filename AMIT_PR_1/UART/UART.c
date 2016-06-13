
#include "UART.h"
#include "UART_LCFG.h"
#include <avr/interrupt.h>

static UartRxCbkFnType USART_CbkRxFun;
static u8 *bufferPtr;
static u8 bufferLength;
static u8 count = 0;

void UART_vidInit(void)
{
	u8 u8Ucsz2;
	u16 u16Ubrr;
	u16Ubrr = ((F_CPU/16)/(UART_CfgData.u32BaudRate))-1;
	
	u8Ucsz2 = (UART_CfgData.u8CharSize & (1<<3)) >> 1;
	UCSRB_REG =	0x00;
	UCSRC_REG |= USART_UCSRC_SEL;
	UCSRC_REG |= ((UART_CfgData.u8CharSize)&~(1<<3)) | (UART_CfgData.u8Parity) | (UART_CfgData.u8StopBit);
	
	UBRRL_REG = (u8) u16Ubrr;
	UBRRH_REG = (u8) (u16Ubrr >> 8);
	
	UCSRB_REG |= USART_RX_ENABLE | USART_TX_ENABLE | USART_RX_INT_ENABLE | (u8Ucsz2);
	sei();
	
}

void UART_vidTransmitByte(u8 u8Byte)
{
	while((UCSRA_REG & USART_UDR_EMPTY) == 0x00)
	;
	UDR_REG = u8Byte;
}

void UART_receiveDataIntoBuffer (UartRxCbkFnType UartCbkFn , u8 * buff , u8 len)
{
	USART_CbkRxFun = UartCbkFn;
	bufferPtr = buff;
	bufferLength = len;
	count = 0;
}

ISR (USART_RXC_vect)
{
	bufferPtr[count++] = UDR_REG;
	if (count == bufferLength)
	{
		USART_CbkRxFun();
		count = 0;
	}
}