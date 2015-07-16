#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <SumoBot.h>  // maybe
//#include <Amp_ino.h>
#include <Servo.h>

SumoBot bot;

void setup() {
  bot.begin();

  bot.pin.turnOn(L1);
}

void loop ()
{
  delay(1000);
  bot.voice.play();
  bot.done();
}
