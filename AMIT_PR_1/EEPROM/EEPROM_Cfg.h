
#ifndef EEPROM_CFG_H_
#define EEPROM_CFG_H_

#define EEPROM_ENABLE_INTERRUPT		0X08
#define EEPROM_MASTER_WRITE_ENABLE	0x04
#define EEPROM_WRITE_ENABLE			0x02
#define EEPROM_READ_ENABLE			0X01

#define EEARL_Reg (u8 volatile *const)0x3E
#define EEARH_Reg (u8 volatile *const)0x3F
#define EEDR_Reg  (u8 volatile *const)0x3D
#define EECR_Reg  (u8 volatile *const)0x3C

#endif /* EEPROM_CFG_H_ */