#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <LineBot.h>
#include <Amp_ino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#include "voice.h"


LineBot bot;

LiquidCrystal_I2C lcd(LC_ADDR, LCEN, LCRW, LCRS, LC4, LC5, LC6, LC7);
 
void setup() 
{
    bot.begin();
    
    lcd.begin(8, 2);
    lcd.print("\x9F\x9E\x9D\x9C\x9C\x9D\x9E\x9F");//     \xA8p\xB8\xB3""e\xBF");
    lcd.setCursor(0, 1);
    lcd.print("\x9B\x9C\x9D\x9E\x9E\x9D\x9C\x9B");
}
 
void loop() 
{
//  String a = "\x9e";
    lcd.setCursor(0, 0);
   // lcd.print();
/*    lcd.print("\x9F\x9F\x9E\x9D\x9D\x9E\x9F\x9F");//     \xA8p\xB8\xB3""e\xBF");
    lcd.setCursor(0, 1);
    lcd.print("\x9B\x9B\x9C\x9D\x9D\x9C\x9B\x9B");
/*delay(100);
  lcd.setCursor(0, 0);
    lcd.print("\x9F\x9E\x9D\x9C\x9C\x9D\x9E\x9F");//     \xA8p\xB8\xB3""e\xBF");
    lcd.setCursor(0, 1);
    lcd.print("\x9B\x9C\x9D\x9E\x9E\x9D\x9C\x9B");
delay(100);
   lcd.setCursor(0, 0);
    lcd.print("\x9E\x9D\x9C\x9B\x9B\x9C\x9D\x9E");//     \xA8p\xB8\xB3""e\xBF");
    lcd.setCursor(0, 1);
    lcd.print("\x9C\x9D\x9E\x9F\x9F\x9E\x9D\x9C");
delay(100);
*/
}
