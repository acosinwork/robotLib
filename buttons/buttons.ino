#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <LineBot.h>
<<<<<<< HEAD
#include <Amp_ino.h>
=======
>>>>>>> bd53fb4c19a7a0e38171eab9ead896de3cef48ee
#include <Servo.h>
#include "buttons.h"


//#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(LC_ADDR, LCEN, LCRW, LCRS, LC4, LC5, LC6, LC7);

LineBot bot;

void setup() {
  // put your setup code here, to run once:

  bot.begin();
  Serial.begin(9600);
  //  pinMode(7, INPUT_PULLUP);
  //    lcd.begin(8, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;

  if (i = checkButtons())
  {
    Serial.println(i);
  }

  Serial.println(bot.buttons.getState(), BIN);

}


