
#include "TMR.h"
#include "TMGR.h"
#include "../SYSTEM_SCNS.h"

void TMGR_Init(void)
{
	TMR_setCountCompare(3); // for 75 ms
	TMR_InitIsrEvery25ms(TMGR_Cyclic25msCbkFn);
}
	
void TMGR_Cyclic1sCbkFn(void)
{
	LockedSCN_CounterDecrement();
}

void TMGR_Cyclic25msCbkFn(void)
{
	welcomeScreen_Update();
}

void TMGR_ChangeFunctionAndTime(void)
{
	TMR_setCountCompare(40); //for 1 sec
	TMR_FunctionCbkChange(TMGR_Cyclic1sCbkFn);
}
