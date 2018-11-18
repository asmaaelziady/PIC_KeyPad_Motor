/**********************************************************************
 * main.c
 *
 *  Created on: May 12, 2017
 *      Author: A_Elziady
 *********************************************************************/


sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;

char keypadport at PORTB;
int i, x = 0;
char password[4];
char keys[13] = {0, /* There is no entry at index 0 */
  '7', '8', '9',
  '4', '5', '6',
  '1', '2', '3',
  'C', '0', '=',
};

int get_password()
{
__retry:
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
  Lcd_Out(1, 1, "Welcome..");
  Delay_ms(1000);
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Out(1, 1, "Your Motor is Off");
  Delay_ms(1000);
  memset(password, 0, 4);
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Out(1, 1, "Enter Password:");
  Delay_ms(1000);

  for (i = 0; i < 3; i++) {
    char c = 0;
    while (!(c = Keypad_Key_Click()));
    password[i] = keys[c];
    Lcd_Chr(2, i+1, '*');
  }
  Delay_ms(100);
  if (strcmp(password, "123") == 0) {return 1;}
  if (strcmp(password, "321") == 0) {return 2;}
  goto __retry;
}

void main()
{
  Lcd_Init();
  Keypad_Init();
  TRISB = 1;
  TRISD = 0;

__reset:
  TRISC = 0b00000100 ;
  PORTC = 0b00000000 ;
  x = get_password();


  if (x == 1) {
    Lcd_Out(1, 1, "Password Matched");
    Lcd_Out(2, 1, "Motor is on..1st dir");
    PORTC = 0b00000001 ;
  } else if (x == 2) {
    Lcd_Out(1, 1, "Password Matched");
    Lcd_Out(2, 1, "Motor is on..2nd dir");
    PORTC = 0b00000010 ;
  } else {
    Lcd_Out(1, 1, "Incorrect Password");
  }

  while (PORTC.B2 != 1);
  goto __reset;
}
