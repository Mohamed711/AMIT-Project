
#include "RTC.h"
#include "RTC_Cfg.h"
#include "../I2C/I2C.h"


void RTC_Init()
{
	TWI_Init();
}

u8 RTC_getHours()
{
	u8 hr;
	TWI_Start();
	TWI_Write(0xD0);
	TWI_Write(HR_ADDRESS);
	TWI_Start();
	TWI_Write(0xD1);
	hr = TWI_Read_With_NACK();
	TWI_Stop();
	hr = (hr&0x0F)+((hr&0x30)>>4)*10;
	return hr;
}
u8 RTC_getSeconds()
{
	u8 hr;
	TWI_Start();
	TWI_Write(0xD0);
	TWI_Write(SEC_ADDRESS);
	TWI_Start();
	TWI_Write(0xD1);
	hr = TWI_Read_With_NACK();
	TWI_Stop();
	hr = (hr&0x0f) + ((hr&0x70)>>4)*10;
	return hr;
}
u8 RTC_getMinutes()
{
	u8 hr;
	TWI_Start();
	TWI_Write(0xD0);
	TWI_Write(MIN_ADDRESS);
	TWI_Start();
	TWI_Write(0xD1);
	hr = TWI_Read_With_NACK();
	TWI_Stop();
	hr = (hr&0x0f)+ ((hr&0x70)>>4)*10;
	return hr;
}
u8 RTC_getDay()
{
	u8 hr;
	TWI_Start();
	TWI_Write(0xD0);
	TWI_Write(DAY_ADDRESS);
	TWI_Start();
	TWI_Write(0xD1);
	hr = TWI_Read_With_NACK();
	TWI_Stop();
	hr = (hr&0x07);
	return hr;
}
u8 RTC_getDate()
{
	u8 hr;
	TWI_Start();
	TWI_Write(0xD0);
	TWI_Write(DATE_ADDRESS);
	TWI_Start();
	TWI_Write(0xD1);
	hr = TWI_Read_With_NACK();
	TWI_Stop();
	hr = (hr&0x0f)+ ((hr&0x30)>>4)*10;
	return hr;
}
u8 RTC_getMonth()
{
	u8 hr;
	TWI_Start();
	TWI_Write(0xD0);
	TWI_Write(MONTH_ADDRESS);
	TWI_Start();
	TWI_Write(0xD1);
	hr = TWI_Read_With_NACK();
	TWI_Stop();
		hr = (hr&0x0f)+ ((hr&0x10)>>4)*10;
	return hr;
}
u8 RTC_getYear()
{
	u8 hr;
	TWI_Start();
	TWI_Write(0xD0);
	TWI_Write(YEAR_ADDRESS);
	TWI_Start();
	TWI_Write(0xD1);
	hr = TWI_Read_With_NACK();
	TWI_Stop();
		hr = (hr&0x0f)+ ((hr&0xF0)>>4)*10;
	return hr;
}
