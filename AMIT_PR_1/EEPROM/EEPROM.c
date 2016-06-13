
#include "eeprom.h"
#include "EEPROM_Cfg.h"

void EEPROM_Write(u16 u16Address , u8 u8Data)
{
	  while(*(EECR_Reg) & EEPROM_WRITE_ENABLE);
	  *(EEARL_Reg) = u16Address;
	  *(EEARH_Reg) = (u16Address>>8);
	  *(EEDR_Reg)  = u8Data;
	  *(EECR_Reg) |= EEPROM_MASTER_WRITE_ENABLE;
	  *(EECR_Reg) |= EEPROM_WRITE_ENABLE;
}

u8 EEPROM_Read(u16 u16Address)
{
	     while(*(EECR_Reg) & EEPROM_WRITE_ENABLE);
	     *(EEARL_Reg) = u16Address;
	     *(EEARH_Reg) = (u16Address >> 8);
	     *(EECR_Reg) |= EEPROM_READ_ENABLE;
	     return *(EEDR_Reg);
}
