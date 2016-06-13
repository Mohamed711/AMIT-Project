
#include "../StdTypes.h"
#include "ADC_Cfg.h"


#if (PREC == PREC_8)
#define READ_RESULT() *(ADCH_REG)
#else
#define READ_RESULT() (((u16)*(ADCL_REG) | ((u16)*(ADCH_REG))<<8))
#endif

#if (PREC == PREC_8)
typedef u8 AdcRetType;
#else
typedef u16 AdcRetType;
#endif

void ADC_Init(void)
{
	/*VREF=AREF and 10 bits precision */
   /*Clear the ADMUX Register*/
   *(ADMUX_REG) = 0x00;
   /*Veref = AREF*/
   *(ADMUX_REG) |= REF_AREF;

   *(ADMUX_REG) |= PREC;
	/*enable ADC, single conversion,500 khz sampling frequency*/
	/*Clear ADCSRA*/
	*(ADCSRA_REG) = 0x00;
	/*Trigering = single*/
	*(ADCSRA_REG) |= TRIG;
	/*Set Dev Factor*/
	*(ADCSRA_REG) |= DEV_FACTOR;
	/*Enable ADC*/
	*(ADCSRA_REG) |= ADC_Enable;
	}

AdcRetType read_adc(u8 channel)
{
	AdcRetType RetVal;
	/*select channel*/
    channel &= 0x1f;
	*(ADMUX_REG) |= channel;
	/*start conversion*/
	*(ADCSRA_REG) |= ADC_START_CONV;
	/*wait until conversion end*/
    while((*(ADCSRA_REG) & ADC_INT_FLAG_MASK) == 0x00);
    /*Clear the flag*/
	*(ADCSRA_REG) |= ADC_INT_FLAG_MASK;
	/*Read the Result*/
	RetVal = READ_RESULT();
	return RetVal;

}

