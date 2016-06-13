#ifndef SPI_CFG_H_
#define SPI_CFG_H_

#include "../StdTypes.h"

// SPI Registers
#define SPCR_REG		*((u8 volatile *const)0x2D)
#define SPDR_REG		*((u8 volatile *const)0x2F)
#define SPSR_REG		*((u8 volatile *const)0x2E)

// clock polarity and clock phase setup
#define u8MODE_0		0x00
#define u8MODE_1		0x04
#define u8MODE_2		0x08
#define u8MODE_3		0x0C

#define u8DOR_MSB		0x00
#define u8DOR_LSB		0x20

#define SPI_INT_EN		0x80
#define SPI_EN			0x40
	
#define SPI_MASTER_EN	0x10
#define SPI_SLAVE_EN	0x00

#define SPI_MSTR_OR_SLAVE SPI_MASTER_EN

#define SPI_INT_FL		0x80
#define SPI_DOUBLE_SP	0x01

#define PRESCALAR_NUM	0x07

#endif /* SPI_CFG_H_ */