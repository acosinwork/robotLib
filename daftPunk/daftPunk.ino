#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <LineBot.h>
#include <Amp_ino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#include "voice.h"

int del=200;


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

  delay(del);
  silence();
  delay(del);
  r();
//  delay(del);
  o();
    delay(del*2);
  k();
  
  

}

void silence()
{
  lcd.setCursor(0, 0);

  for (int i = 0; i < 8; ++i)
    lcd.print(w[0]);

  lcd.setCursor(0, 1);

  for (int i = 0; i < 8; ++i)
    lcd.print(b[0]);
}

void r()
{
  lcd.setCursor(0, 0);
  lcd.print(w[0]);
  lcd.print(w[0]);

  lcd.print(w[1]);
  lcd.print(w[2]);

  lcd.print(w[2]);
  lcd.print(w[1]);

  lcd.print(w[0]);
  lcd.print(w[0]);

  lcd.setCursor(0, 1);

  lcd.print(b[0]);
  lcd.print(b[0]);

  lcd.print(b[1]);
  lcd.print(b[2]);

  lcd.print(b[2]);
  lcd.print(b[1]);

  lcd.print(b[0]);
  lcd.print(b[0]);
}

void o()
{
  lcd.setCursor(0, 0);
  lcd.print(w[0]);
  lcd.print(w[1]);

  lcd.print(w[3]);
  lcd.print(w[4]);

  lcd.print(w[4]);
  lcd.print(w[3]);

  lcd.print(w[1]);
  lcd.print(w[0]);

  lcd.setCursor(0, 1);

  lcd.print(b[0]);
  lcd.print(b[0]);

  lcd.print(b[2]);
  lcd.print(b[4]);

  lcd.print(b[4]);
  lcd.print(b[2]);

  lcd.print(b[0]);
  lcd.print(b[0]);
}

void k()
{
  lcd.setCursor(0, 0);
  lcd.print(w[0]);
  lcd.print(w[2]);

  lcd.print(w[2]);
  lcd.print(w[3]);

  lcd.print(w[3]);
  lcd.print(w[2]);

  lcd.print(w[2]);
  lcd.print(w[0]);

  lcd.setCursor(0, 1);

  lcd.print(b[1]);
  lcd.print(b[2]);

  lcd.print(b[2]);
  lcd.print(b[2]);

  lcd.print(b[2]);
  lcd.print(b[2]);

  lcd.print(b[2]);
  lcd.print(b[1]);
}



