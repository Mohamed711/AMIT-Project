
#ifndef SYSTEM_SCNS_H_
#define SYSTEM_SCNS_H_

#include "StdTypes.h"
#include "LCD/LCD.h"
#include "LCD/LCD_Cfg.h"
#include "KPD/KEYPAD.h"
#include "KPD/KEYPAD_Cfg.h"
#include "EEPROM/EEPROM.h"
#include "Timer/TMGR.h"
#include "TC72/TC72.h"
#include "LM35/LM35.h"
#include "RTC/RTC.h"
#include "UART/UART.h"

#define PASSWORD_LENGTH		0x06
#define SCN_ADDRESS			0x30

#define IS_DIGIT(x)		((x)>='0'&&(x)<='9')

typedef enum {
	WELCOME_SCREEN,
	PASSWORD_ENTRY,
	SYSTEM_LOCKED,
	SYSTEM_ENTRY_SCN,
	NEW_PASS_SCN,
	MAIN_SCN
}screen;

screen currentScreen;
	
/* Functions prototypes */

/* screen initialization functions */
void WelcomeScreen_Init();
void PasswordEntrySCN_Init();
void LockedSCN_Init();
void systemEntrySCN_Init();
void PasswordChangeSCN_Init();
void MainSCN_Init();

/* screen update functions */
void PasswordEntrySCN_Update(u8 trialsNumber);
void LockedSCN_Update(u8 countValue);
void welcomeScreen_Update(); // call back function to move the word at the welcome screen 
void MainSCN_Update();

/* check the entered password if its the default or the saved one */
u8 u8Check_Password(u8* password);

/* initialize the system from the last state before closing or reset the system */
void system_vidInitialize();

/* KPD key is pressed on the password entry screen */
void KPD_PasswordEntered();

/* call back function to decrement the counter when the system is locked */
void LockedSCN_CounterDecrement();

#endif /* SYSTEM_SCNS_H_ */