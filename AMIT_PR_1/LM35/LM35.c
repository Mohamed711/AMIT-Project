#include "../ADC/ADC.h"
#include "../StdTypes.h"


void LM35_Init()
{
	ADC_Init();
}

float LM35_TempRead()
{
	u16 temp;
	float y;
	
	temp = read_adc(0);
	y= (temp*5)/1023.0;
	y *= 100;
	return y;
}