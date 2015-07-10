#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <SumoBot.h>  // maybe
//#include <Amp_ino.h>
#include <Servo.h>

#define MOVE_TIME 500
#define STEP_COUNT 8

#define FORWARD 0
#define BACK    1
#define LEFT    2
#define RIGHT   3

SumoBot bot;

int steps[STEP_COUNT];

int currentStep = 0;

void setup() {

  bot.begin();

  bot.pin.turnOn(L1);

  bot.buttons.onPress(S1, goForward);
  bot.buttons.onPress(S2, goBack);
  bot.buttons.onPress(S3, goLeft);
  bot.buttons.onPress(S4, goRight);

  while (currentStep < STEP_COUNT)
  {
    bot.buttons.check();
  }

  for (int i = 0; i < 3; ++i)
  {
    delay(1000);
    bot.beep(1000 + i * 50);

  }
}

void loop ()
{
  --currentStep;

  switch (steps[currentStep])
  {
    case FORWARD:
      bot.speed(100, 100);
      break;
    case BACK:
      bot.speed(-100, -100);
      break;
    case LEFT:
      bot.speed(-100, 100);
      break;
    case RIGHT:
      bot.speed(100, -100);
  }

  delay(MOVE_TIME);

  if (!currentStep)
  {
    bot.stop();
    delay(1000);

    bot.voice.play();
    bot.done();
  }
}

void goForward()
{
  bot.beep();
  steps[currentStep] = FORWARD;
  ++currentStep;
}
void goBack()
{
  bot.beep();
  steps[currentStep] = BACK;
  ++currentStep;
}
void goLeft()
{
  bot.beep();
  steps[currentStep] = LEFT;
  ++currentStep;
}
void goRight()
{
  bot.beep();
  steps[currentStep] = RIGHT;
  ++currentStep;
}




