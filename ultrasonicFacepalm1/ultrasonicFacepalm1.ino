#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <Amp_ino.h>
#include <LineBot.h>
#include <LiquidCrystal_I2C.h>
#include <PID_v1.h>
#include <Ultrasonic.h>
#include <Servo.h>


#define STEP_COUNT           6
#define LOOKUP_START_DEG     -60
#define LOOKUP_END_DEG       60
#define DEG_STEP             (LOOKUP_END_DEG-LOOKUP_START_DEG)/STEP_COUNT

int power = 40;
int error = 0;
int needDistance = 40;

bool rise = false;

LineBot bot;

Servo myservo;  // create servo object to control a servo

int trig = P11;
int echo = P12;
Ultrasonic ultrasonic(trig, echo);

void setup() {


  Serial.begin(9600);
  // put your setup code here, to run once:
  bot.begin();

  myservo.attach(P3);  // attaches the servo on pin 9 to the servo object

}

void loop() {
  // put your main code here, to run repeatedly:



  int angle, distance;
  
  

  for (int i = 0; i < STEP_COUNT; ++i)
  {

    if (rise)
    {
      angle = LOOKUP_START_DEG + i * DEG_STEP;
    } else {
      angle = LOOKUP_END_DEG - i * DEG_STEP;
    }

    lookThis(angle);


    distance = getDistanceCentimeter();

    if (distance < needDistance)
    {

      bot.speed(0.0);
      delay(50);

      int mult = cos(angle * PI / 180);

      //       bot.speed(-rotatePower, -rotatePower);
      //       delay(20);


      if (angle < 0)
        bot.speed(-power, - mult * power);
      else
        bot.speed(-mult * power, -power);

      delay(300 + error * 100);
      ++error;
    } else
    {
      error = 0;
      bot.speed(power, power);
    }

  }
  rise = !rise;
}



int getDistanceCentimeter()
{

  static float FK = 0.2;
  static int dist = 0;

  for (int i = 0; i < 3; ++i)
  {
    delay(25);

    int currentDist;
    if (!(currentDist = ultrasonic.CalcDistance(ultrasonic.timing(), Ultrasonic::CM)))
      currentDist = ultrasonic.CalcDistance(8000, Ultrasonic::CM);

    dist = (1 - FK) * dist + FK * currentDist;

    //    dist = (1 - FK) * dist + FK * ultrasonic.CalcDistance(ultrasonic.timing(), Ultrasonic::CM);
  }
  tone(BUZZER, 6000 - (dist * 20), 2);

  //  Serial.println(dist);
  

  return dist; //ultrasonic.CalcDistance(trustedMicrosecond, Ultrasonic::CM); //this result unit is centimeter
}


void lookThis(int grad)
{
  myservo.write(grad + 90);
}



