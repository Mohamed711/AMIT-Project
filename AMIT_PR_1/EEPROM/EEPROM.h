
#ifndef EEPROM_H_
#define EEPROM_H_

#include "../StdTypes.h"

void EEPROM_Write(u16 u16Address , u8 u8Data);
u8 EEPROM_Read(u16 u16Address);

#endif /* EEPROM_H_ */