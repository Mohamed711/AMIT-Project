
#ifndef LCD_H_
#define LCD_H_

#include "../StdTypes.h"

void lcd_displayChar(u8 data,u8 LcdID);
void lcd_Init(void);
void lcd_gotoxy(u8 x , u8 y , u8 LcdID);
void lcd_clrScreen(u8 LcdID);
void lcd_dispString(u8 * ptr,u8 LcdID);
void lcd_disp_string_xy(u8 * ptr , u8 y , u8 x,u8 LcdID);
void lcd_disp_int(u8 num,u8 LcdID);
void lcd_disp_float(float num,u8 LcdID);

#endif /* LCD_H_ */