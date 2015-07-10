#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <SumoBot.h>
#include <Servo.h>
//#include "buttons.h"


//#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(LC_ADDR, LCEN, LCRW, LCRS, LC4, LC5, LC6, LC7);

SumoBot bot;

void setup() {
  // put your setup code here, to run once:

  bot.begin();

  bot.buttons.onPress(S1, doIt1);
  bot.buttons.onPress(S2, doIt2);
  bot.buttons.onPress(S3, doIt3);
  bot.buttons.onPress(S4, doIt4);

  bot.buttons.onRelease(S1, doIt3);
  

  Serial.begin(9600);
  //  pinMode(7, INPUT_PULLUP);
  //    lcd.begin(8, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  /*
    if (i = checkButtons())
    {
      Serial.println(i);
    }
  */
  Serial.println(bot.buttons.check(), BIN);
}

void doIt1()
{
  bot.pin.turnOn(L1);
}

void doIt2()
{
  bot.pin.turnOff(L1);
}

void doIt3()
{
  bot.pin.turnOn(L2);
}

void doIt4()
{
  bot.pin.turnOff(L2);
}


