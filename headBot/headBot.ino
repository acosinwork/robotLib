#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <SumoBot.h>
#include <Amp_ino.h>
#include <Servo.h>
#include <UltrasonicScan.h>


SumoBot bot;
int maxSpeed = 60;
int minDistanceAngle, minDistance;

float radToDeg = PI / 180;

void setup() {
  // put your setup code here, to run once:
  
  bot.begin();

  bot.head.attachUltrasonic(P11, P12);
  bot.head.attachServo(P3);

  bot.head.setLookUpSector(-80, 80);

  bot.head.lookAt(0);
  minDistance = bot.head.getDistance();


  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (bot.head.sectorScaning()) {
    bot.speed(maxSpeed * cos(minDistanceAngle * radToDeg) + maxSpeed* sin(minDistanceAngle * radToDeg), maxSpeed * cos(minDistanceAngle * radToDeg) - maxSpeed*sin(minDistanceAngle * radToDeg));
    minDistance = 1000;
  }
  else
  {
    if (minDistance > bot.head.getDistance()) {
      minDistance = bot.head.getDistance();
      minDistanceAngle = bot.head.getAngle();
    }
  }

}
