#ifndef UART_CFG_H_
#define UART_CFG_H_

#define UDR_REG				*((u8 volatile *const)0x2C)
#define UCSRA_REG			*((u8 volatile *const)0x2B)
#define UCSRB_REG			*((u8 volatile *const)0x2A)
#define UCSRC_REG			*((u8 volatile *const)0x40)
#define UBRRH_REG			*((u8 volatile *const)0x40)
#define UBRRL_REG			*((u8 volatile *const)0x29)

#define USART_RX_COMPLETE	0x80
#define USART_TX_COMPLETE	0x40
#define USART_UDR_EMPTY		0x20

#define USART_RX_INT_ENABLE 0x80
#define USART_TX_INT_ENABLE	0x40
#define USART_TX_ENABLE		0x08
#define USART_RX_ENABLE		0x10

#define USART_UCSRC_SEL		0x80

#define USART_ASYNC_MODE	0x00
#define USART_SYNC_MODE		0x40

#define CH_SIZE_5			0x00
#define CH_SIZE_6			0x02
#define CH_SIZE_7			0x04
#define CH_SIZE_8			0x06
#define CH_SIZE_9			0x0E

#define PARITY_NONE			0x00
#define PARITY_EVEN			0x20
#define PARITY_ODD			0x30

#define STOP_1				0x00
#define STOP_2				0x08


#endif /* UART_CFG_H_ */