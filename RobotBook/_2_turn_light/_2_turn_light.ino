#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <SumoBot.h>
#include <Amp_ino.h>
#include <Servo.h>

SumoBot bot;

void setup() {
  bot.pin.turnOn(L1);
}

void loop ()
{
}
