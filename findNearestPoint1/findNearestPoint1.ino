#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <LineBot.h>
#include <LiquidCrystal_I2C.h>
#include <PID_v1.h>
#include <Ultrasonic.h>
#include <Servo.h>

#define DEG_STEP             5
#define LOOKUP_START_DEG     -90
#define LOOKUP_END_DEG       90

/*
#define LOOKUP_MEASURE_COUNT (LOOKUP_END_DEG - LOOKUP_START_DEG) / DEG_STEP

#define DEG    0
#define DIST   1
*/

struct POINT {
  int distance;
  int degree;
} nearestPoint;

int power = 50;

//int nearestPointDeg;

double Setpoint, Input, Output;

double Kp = 0.5, Ki = 0.0, Kd = 0.0;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


LineBot bot;

Servo myservo;  // create servo object to control a servo

int trig = P11;
int echo = P12;
Ultrasonic ultrasonic(trig, echo);

void setup() {
  // put your setup code here, to run once:
  bot.begin();

  myservo.attach(P3);  // attaches the servo on pin 9 to the servo object

  lookThis(LOOKUP_START_DEG);

  int constantDist = 3000;

  while (constantDist != getDistanceCentimeter())
  {
    delay(100);
    constantDist = getDistanceCentimeter();
  }

  myPID.SetSampleTime(100);
  myPID.SetOutputLimits(-power, power);

  myPID.SetMode(AUTOMATIC);

  nearestPointDeg = findNearestPoint();

}

void loop() {
  // put your main code here, to run repeatedly:
  if (nearestPointDeg > 0)
    Input = nearestPointDeg = findNearestPoint(0, nearestPointDeg + 10, 2);
  else if (nearestPointDeg < 0)
    Input = nearestPointDeg = findNearestPoint(nearestPointDeg - 10, 0, 2);
  else
    Input = nearestPointDeg = findNearestPoint(nearestPointDeg - 5, nearestPointDeg + 5, 2);




  if (myPID.Compute())
  {
    int uSpeed = Output;
    int brake = (abs(uSpeed) >> 1);

    bot.speed(power + uSpeed - brake, power - uSpeed - brake);
  }

  delay(300);

  bot.speed(0, 0);



  /*  while (!uDigitalRead(S1))
      ;;
  */
}

int findNearestPoint(POINT* needToFind,int startAngle, int endAngle, int stepAngle)
{
  static bool rise = true;

  enum measureData {degree, distance};

  int measureCount = (endAngle - startAngle) / stepAngle;

  int measures[measureCount][2];

  for (int i = 0; i < measureCount; ++i)
  {
    if (rise)
    {
      measures[i][degree] = startAngle + i * stepAngle;
    } else {
      measures[i][degree] = endAngle - i * stepAngle;
    }

    lookThis(measures[i][degree]);

    measures[i][distance] = getDistanceCentimeter();

  }

  rise = !rise;

  int lowerDistField = 0;
  int nearestPoint = measures[0][distance];

  for (int i = 0; i < measureCount; ++i)
  {
    if (nearestPoint > measures[i][distance])
    {
      lowerDistField = i;
      nearestPoint = measures[i][distance];
    }
  }

  //  lookThis(measures[lowerDistField][degree]);

  return measures[lowerDistField][degree];

}

int getDistanceCentimeter()
{

  static float FK = 0.1;
  static int dist = 0;

  for (int i = 0; i < 2; ++i)
  {
    delay(30);
    dist = (1 - FK) * dist + FK * ultrasonic.CalcDistance(ultrasonic.timing(), Ultrasonic::CM);
  }
  tone(BUZZER, 6000 - (dist * 50), 50);

  return dist; //ultrasonic.CalcDistance(trustedMicrosecond, Ultrasonic::CM); //this result unit is centimeter
}

void lookThis(int grad)
{
  myservo.write(grad + 90);
}

