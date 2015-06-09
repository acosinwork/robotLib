#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <SumoBot.h>
#include <Amp_ino.h>
#include <Servo.h>
//#include <UltrasonicScan.h>


SumoBot bot;

//UltrasonicFiltered uf(5,6);

void setup() {
  // put your setup code here, to run once:
  
  bot.head.attachUltrasonic(P11,P12);
  bot.head.attachServo(P3);
  
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  bot.head.lookAt(0);
  Serial.println(bot.head.getDistance());
  
  bot.head.lookAt(15);
  

}
