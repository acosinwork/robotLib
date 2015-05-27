#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <LineBot.h>
#include <LiquidCrystal_I2C.h>

#define WHEEL_DIAMETER 6.6
#define WHEEL_CURVE WHEEL_DIAMETER*PI

volatile int leftCount = 0;
volatile int rightCount = 0;
LineBot bot;

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
attachInterrupt(0,leftWheel, FALLING);
attachInterrupt(1,rightWheel, FALLING);


}

void loop() {
  // put your main code here, to run repeatedly:
  
  bot.speed(20,20);
  
  Serial.print("left - ");
  Serial.println(leftCount);
  Serial.print("right - ");
  Serial.println(rightCount);

}

void leftWheel()
{
++leftCount;
}

void rightWheel()
{
  ++rightCount;
}
