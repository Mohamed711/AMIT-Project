#include "SYSTEM_SCNS.h"

#define WRONG_PASSWORD		0x00
#define RIGHT_PASSWORD		0x01

#define LCD_WIDTH			16

#define MOVE_RIGHT			0x00
#define MOVE_LEFT			0x01

/* EEPROM Addresses */
#define TRIALS_ADDRESS		0x06
#define COUNTING_ADDRESS	0x07
#define COUNTING_TEMP_ADDRESS	0x08
	
	
/* variables */
static u8 welcomeWordLength = 0;
static u8 trialsNumber;
static u8 countValue;
static u8 countTemp;
static u8 newPassword[PASSWORD_LENGTH];

extern u8 welcome[] ;
extern u8 defaultPassword[];
extern u8 PasswordAddresses[];
extern u8 newPasswordReceived;

/* function prototype */
static u8 computeSentenceLength(u8 *ptr);
static void getUARTRxData();
static void LM35_Update();
static void TC72_Update();
static void RTC_Update();

/* Functions definitions */
void WelcomeScreen_Init()
{
	currentScreen = WELCOME_SCREEN;
	lcd_clrScreen(LCD_ID0);
	welcomeWordLength = computeSentenceLength(welcome);
}
void PasswordEntrySCN_Init()
{
	currentScreen = PASSWORD_ENTRY;
	TMGR_ChangeFunctionAndTime();
	lcd_clrScreen(LCD_ID0);
	lcd_disp_string_xy((u8*)"password:",0,0,LCD_ID0);
	lcd_disp_string_xy((u8*)"use KPD--Trial:",1,0,LCD_ID0);
	PasswordEntrySCN_Update(trialsNumber);
}
void LockedSCN_Init()
{
	currentScreen = SYSTEM_LOCKED;
	TMGR_ChangeFunctionAndTime();
	lcd_clrScreen(LCD_ID0);
	lcd_dispString((u8*)"system is locked",LCD_ID0);
	lcd_disp_string_xy((u8*)"counting :",1,0,LCD_ID0);
	LockedSCN_Update(countTemp);
}
void systemEntrySCN_Init()
{
	currentScreen = SYSTEM_ENTRY_SCN;
	lcd_clrScreen(LCD_ID0);
	lcd_dispString((u8*)"1: change pass.",LCD_ID0);
	lcd_disp_string_xy((u8*)"2: system entry",1,0,LCD_ID0);
}
void PasswordChangeSCN_Init()
{
	currentScreen = NEW_PASS_SCN;
	lcd_clrScreen(LCD_ID0);
	lcd_disp_string_xy((u8*)"Enter new pass",0,0,LCD_ID0);
	lcd_disp_string_xy((u8*)"using UART",1,0,LCD_ID0);
	UART_receiveDataIntoBuffer(getUARTRxData,newPassword,PASSWORD_LENGTH);
}
void MainSCN_Init()
{
	currentScreen = MAIN_SCN;
	lcd_clrScreen(LCD_ID0);
	lcd_disp_string_xy((u8*)"L:",0,0,LCD_ID0);
	lcd_disp_string_xy((u8*)"T:",1,0,LCD_ID0);
	MainSCN_Update();
}

/* screen update functions */
void PasswordEntrySCN_Update(u8 trialsNumber){
	lcd_gotoxy(1,15,LCD_ID0);
	lcd_disp_int(trialsNumber,LCD_ID0);
}
void LockedSCN_Update(u8 countValue)
{
	lcd_disp_string_xy((u8*)"  ",1,11,LCD_ID0);
	lcd_gotoxy(1,11,LCD_ID0);
	lcd_disp_int(countValue,LCD_ID0);
}
void welcomeScreen_Update()
{
	static s8 LoopIndex = 0;
	static u8 direction = MOVE_RIGHT;

	if (direction == MOVE_RIGHT)
	{
		lcd_disp_string_xy(welcome,0,LoopIndex,LCD_ID0);
		if (LoopIndex != 0)
		{
			lcd_disp_string_xy((u8*)" ",0,LoopIndex-1,LCD_ID0);
		}

		LoopIndex++;
		
		if (LoopIndex > (LCD_WIDTH-welcomeWordLength))
		{
			direction = MOVE_LEFT;
			LoopIndex = LCD_WIDTH-welcomeWordLength;
		}
	}
	else
	{
		LoopIndex--;
		lcd_disp_string_xy(welcome,0,LoopIndex,LCD_ID0);
		lcd_disp_string_xy((u8*)" ",0,LoopIndex+welcomeWordLength,LCD_ID0);
		
		if (LoopIndex == 0)
		{
			direction = MOVE_RIGHT;
			LoopIndex = 1;
		}
	}
}
void MainSCN_Update()
{
	LM35_Update();
	TC72_Update();
	RTC_Update();
}

/* call back function to decrement the counter when the system is locked */
void LockedSCN_CounterDecrement()
{
	if (currentScreen == SYSTEM_LOCKED)
	{
		countTemp--;
		if (countTemp == 0)
		{
			PasswordEntrySCN_Init();
		}
		else 
		{
			LockedSCN_Update(countTemp);
			EEPROM_Write(COUNTING_TEMP_ADDRESS,countTemp);
		}
	}
}

/* load the last state of the system */
void system_vidInitialize()
{
	u8 val;
	val = EEPROM_Read(SCN_ADDRESS);

	if (val == SYSTEM_LOCKED)
	{
		trialsNumber =  EEPROM_Read(TRIALS_ADDRESS);
		countValue = EEPROM_Read(COUNTING_ADDRESS);
		countTemp = EEPROM_Read(COUNTING_TEMP_ADDRESS);
		LockedSCN_Init();
	}
	else if (val == PASSWORD_ENTRY )
	{
		trialsNumber =  EEPROM_Read(TRIALS_ADDRESS);
		countValue = EEPROM_Read(COUNTING_ADDRESS);
		countTemp = EEPROM_Read(COUNTING_TEMP_ADDRESS);
		PasswordEntrySCN_Init();
	}
	else
	{
		WelcomeScreen_Init();
		trialsNumber = 0;
		countTemp = 0;
		countValue = 0;
	}
}

/* KPD button is pressed in the password entry screen */
void KPD_PasswordEntered()
{
	u8 KeypadInput;
	static u8 passCount = 0;
	static u8 passEntered[6];
	
	KeypadInput = KPD_Getkey(KPD_ID0);

	if (IS_DIGIT(KeypadInput))
	{
		if (passCount < 6)
		{
			lcd_disp_string_xy((u8*)"*",0,10+passCount,LCD_ID0);
			passEntered[passCount] = KeypadInput;
			passCount++;
		}
	}
	else if (KeypadInput == '*' && passCount != 0)
	{
		lcd_disp_string_xy((u8*)" ",0,9+passCount,LCD_ID0);
		passCount--;
	}
	else if (KeypadInput == '#' && passCount == 6)
	{
		u8 passwordRight;
		passwordRight = u8Check_Password(passEntered);
		
		if (passwordRight == RIGHT_PASSWORD)
		{
			systemEntrySCN_Init();
		}
		else
		{
			if (trialsNumber == 2)
			{
				trialsNumber = 0;
				countValue += 5;
				countTemp = countValue;
				passCount = 0;
				LockedSCN_Init();
				EEPROM_Write(COUNTING_ADDRESS,countValue);
				EEPROM_Write(COUNTING_TEMP_ADDRESS,countTemp);
			}
			else
			{
				trialsNumber++;
				PasswordEntrySCN_Update(trialsNumber);
			}
			EEPROM_Write(TRIALS_ADDRESS,trialsNumber);
		}
	}
}

/* compare the entered password with the default and the saved one */
u8 u8Check_Password(u8* password)
{
	u8 LoopIndex;
	u8 passwordFlg = 1;
	u8 defaultFlg = 1;
	u8 RetVal;
	for (LoopIndex = 0; LoopIndex < PASSWORD_LENGTH ; LoopIndex++)
	{
		if (password[LoopIndex] != EEPROM_Read(PasswordAddresses[LoopIndex]))
		{
			passwordFlg = 0;
		}
		if (password[LoopIndex] != defaultPassword[LoopIndex])
		{
			defaultFlg = 0;
		}
	}
	if (passwordFlg || defaultFlg)
	{
		RetVal = RIGHT_PASSWORD;
	}
	else
	{
		RetVal = WRONG_PASSWORD;
	}
	return RetVal;
}

/* compute the length of the welcome sentence */
static u8 computeSentenceLength(u8 *ptr)
{
	u8 length = 0;
	
	while (*ptr != '\0')
	{
		length++;
		ptr++;
	}
	return length;
}

/* Update the main screen functions */
static void LM35_Update()
{
	float temperature;
	temperature = LM35_TempRead();
	lcd_gotoxy(0,2,LCD_ID0);
	lcd_disp_float(temperature,LCD_ID0);
}

static void TC72_Update()
{
	float temperature;
	temperature = TC72_floatTempRead();
	lcd_gotoxy(1,2,LCD_ID0);
	lcd_disp_float(temperature,LCD_ID0);
}

static void RTC_Update()
{
	u8 val;
	
	lcd_gotoxy(0,8,LCD_ID0);
	val = RTC_getHours();
	lcd_disp_int(val,LCD_ID0);
	lcd_displayChar(':',LCD_ID0);
	val = RTC_getMinutes();
	lcd_disp_int(val,LCD_ID0);
	lcd_displayChar(':',LCD_ID0);
	val = RTC_getSeconds();
	lcd_disp_int(val,LCD_ID0);

	lcd_gotoxy(1,8,LCD_ID0);
	val = RTC_getDate();
	lcd_disp_int(val,LCD_ID0);
	lcd_displayChar('/',LCD_ID0);
	val = RTC_getMonth();
	lcd_disp_int(val,LCD_ID0);
	lcd_displayChar('/',LCD_ID0);
	val = RTC_getYear();
	lcd_disp_int(val,LCD_ID0);
}

static void getUARTRxData()
{
	u8 LoopIndex;
	u8 right_pass = 1;
	
	for (LoopIndex = 0; LoopIndex < 6; LoopIndex++)
	{
		if (IS_DIGIT(newPassword[LoopIndex]) == 0)
		{
			right_pass = 0;
			break;
		}
	}
	
	if (right_pass == 1)
	{
		for (LoopIndex = 0; LoopIndex < 6; LoopIndex++)
		{
			EEPROM_Write(PasswordAddresses[LoopIndex],newPassword[LoopIndex]);
		}
	}
	newPasswordReceived = 1;
}