
#include <avr/io.h>
#include <avr/interrupt.h>

#include "TMR.h"
#include "../StdTypes.h"

static CylicCbkFnType TMR_CylicFunPtr;
static u8 count = 0;
static u8 countCompare = 0;

void TMR_InitIsrEvery25ms(CylicCbkFnType CylicCbkFnPtr)
{
	sei();
	TCCR0 = 0x00;
	TCCR0 |= 1<< WGM01 | 1 << CS00 | 1<<CS02 ;
	TIMSK = 0x00;
	OCR0 = 200;
	TIMSK |= 1<<OCIE0;
	TMR_CylicFunPtr = CylicCbkFnPtr;
}

void TMR_FunctionCbkChange(CylicCbkFnType CylicCbkFnPtr)
{
	TMR_CylicFunPtr = CylicCbkFnPtr;
}

void TMR_setCountCompare(u8 val)
{
	count = 0;
	countCompare = val;
}

ISR(TIMER0_COMP_vect)
{
	count++;
	if (count == countCompare)
	{
		TMR_CylicFunPtr();
		count = 0;
	}
}

