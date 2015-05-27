#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <LineBot.h>
#include <LiquidCrystal_I2C.h>
#include <PID_v1.h>
#include <Ultrasonic.h>
#include <Servo.h>

int trig = P11;
int echo = P12;
Ultrasonic ultrasonic(trig, echo);
unsigned long timeServo = 0;
bool rise = true;

int alpha = 10;
int degStep = 1;

float FK = 0.1;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


int dist;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(P3);  // attaches the servo on pin 9 to the servo object
  myservo.write(alpha);

  Serial.begin(9600);
  }

void loop() {
  // put your main code here, to run repeatedly:

int distRaw = ultrasonic.CalcDistance(ultrasonic.timing(), Ultrasonic::CM);

dist = (1-FK)*dist + FK*distRaw;

  Serial.println(dist);//getDistanceCentimeter());


  if (millis() - timeServo > 50)
  {
    if (rise)
    {
      alpha += degStep;
      if (alpha >= 180)
        rise = false;
    }
    else
    {
      alpha -= degStep;
      if (alpha <= 0)
        rise = true;
    }

    myservo.write(alpha);
    timeServo = millis();
  }

delay(100);
}

double getDistanceCentimeter()
{
  unsigned long microsec[16];// = ultrasonic.timing();
  unsigned long microSumm = 0;

  for (int i = 0; i < 16; ++i)
  {
    while (((microsec[i] = ultrasonic.timing()) > 30000) || (microsec[i] < 6));
    ;;
    microSumm += microsec[i];
    delay(10);
  }

  microSumm >>= 4;

  unsigned long trustedMicrosecond = 0;
  int trustedCounter = 0;
  for (int i = 0; i < 16; ++i)
  {
    if (microsec[i] < microSumm)
    {
      trustedMicrosecond += microsec[i];
      ++trustedCounter;
    }
  }

  trustedMicrosecond /= trustedCounter;

  return ultrasonic.CalcDistance(trustedMicrosecond, Ultrasonic::CM); //this result unit is centimeter
}
