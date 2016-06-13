#include "SYSTEM_SCNS.h"

u8 defaultPassword[PASSWORD_LENGTH]="000000";
u8 PasswordAddresses[PASSWORD_LENGTH] = {0x00,0x01,0x02,0x03,0x04,0x05};
u8 welcome[] = "Welcome";


u8 newPasswordReceived = 0;
	
int main(void)
{

	lcd_Init();
	KPD_Init();
	TMGR_Init();
	TC72_Init(TC72_MODE_CONT);
	LM35_Init();
	RTC_Init();
	UART_vidInit();
	
	/* Check the system last state and initialize it 
	 * Either by restoring the last state of the system
	 * or by reset the system and start it
	 */
	system_vidInitialize();
				
	while(1)
	{	
		if (currentScreen == WELCOME_SCREEN)
		{	
			if (KPD_Getkey(KPD_ID0) != 0 )
			{
				PasswordEntrySCN_Init();
			}
		}
		else if (currentScreen == PASSWORD_ENTRY)
		{
			KPD_PasswordEntered();
		}
		else if (currentScreen == SYSTEM_ENTRY_SCN)
		{
			u8 PressedKey;
			PressedKey = KPD_Getkey(KPD_ID0);
			if (PressedKey == '1')
			{
				PasswordChangeSCN_Init();
			}
			else if (PressedKey == '2')
			{
				MainSCN_Init();
			}
		}
		else if (currentScreen == NEW_PASS_SCN)
		{	
			if (newPasswordReceived == 1)
			{
				systemEntrySCN_Init();		
			}
		}
		else if (currentScreen == MAIN_SCN)
		{
			u8 PressedKey;
			PressedKey = KPD_Getkey(KPD_ID0);
			MainSCN_Update();
			if (PressedKey == '*')
			{
				systemEntrySCN_Init();
			}
		}
		EEPROM_Write(SCN_ADDRESS,currentScreen);
	}	
}

