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
  bot.speed(200, 200);
  delay(3000);

  bot.speed(-100, -100);

  delay(1000);

  bot.stop();
  delay(1000);
  
  bot.voice.play();
  bot.done();
}
