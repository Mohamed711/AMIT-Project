
#ifndef TMR_H_
#define TMR_H_

#include "../StdTypes.h"

typedef void (*CylicCbkFnType)(void);

void TMR_setCountCompare(u8 val);
void TMR_InitIsrEvery25ms(CylicCbkFnType CylicCbkFnPtr);
void TMR_FunctionCbkChange(CylicCbkFnType CylicCbkFnPtr);

#endif /* TMR_H_ */