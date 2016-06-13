#ifndef UART_H_
#define UART_H_

#include "../StdTypes.h"


typedef void (*UartRxCbkFnType)(void);
void UART_vidInit(void);
void UART_vidTransmitByte(u8 u8Byte);
u8 UART_u8RecieveByte(void);
void UART_receiveDataIntoBuffer (UartRxCbkFnType UartCbkFn , u8 * buff , u8 len);


#endif /* UART_H_ */