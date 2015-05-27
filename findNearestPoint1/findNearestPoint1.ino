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
#define HALF_LOOKUP_SECTOR   20


enum State{
  findTheWall,
  
}


/*
#define LOOKUP_MEASURE_COUNT (LOOKUP_END_DEG - LOOKUP_START_DEG) / DEG_STEP

#define DEG    0
#define DIST   1
*/

int nearestPointAngle, nearestPointDistance;
int oldDist = 0;

int power = 50;

//int nearestPointDeg;

double Setpoint, Input, Output;

double Kp = 0.1, Ki = 0.0, Kd = 0.0;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


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

  lookThis(LOOKUP_START_DEG);

  int nearestPointDistance = 20000; // максимум короче

  while (nearestPointDistance != getDistanceCentimeter())
  {
    delay(100);
    nearestPointDistance = getDistanceCentimeter();
  }

  myPID.SetSampleTime(100);
  myPID.SetOutputLimits(-power, power);

  myPID.SetMode(AUTOMATIC);



}

void loop() {
  // put your main code here, to run repeatedly:

  bool state = findTheWall(15);

  while (state)
    ;;

}
void findNearestPoint()
{
  findNearestPoint(LOOKUP_START_DEG, LOOKUP_END_DEG, DEG_STEP);
}

void findNearestPoint(int startAngle, int endAngle, int stepAngle)
{
  static bool rise = true;

  enum measureData {angle, distance};

  int measureCount = (endAngle - startAngle) / stepAngle;

  int measures[measureCount][2];

  for (int i = 0; i < measureCount; ++i)
  {
    if (rise)
    {
      measures[i][angle] = startAngle + i * stepAngle;
    } else {
      measures[i][angle] = endAngle - i * stepAngle;
    }

    lookThis(measures[i][angle]);
    if (measures[i][angle] == startAngle)
      delay(abs(measures[i][angle] - nearestPointAngle));

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

  int i = 0;
  while ((measures[lowerDistField + i][distance] == nearestPoint) && (lowerDistField + i < measureCount))
    ++i;

  lowerDistField += i / 2;




  oldDist = nearestPointDistance;
  nearestPointAngle = measures[lowerDistField][angle];
  nearestPointDistance = measures[lowerDistField][distance];


}

int getDistanceCentimeter()
{

  static float FK = 0.25;
  static int dist = 0;

  for (int i = 0; i < 3; ++i)
  {
    delay(22);

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

bool findTheWall(int minDistance)
{
  if (nearestPointDistance > 1.2 * oldDist)
  {
    bot.speed(0, 0);

    findNearestPoint();



  }  else  {

    int lookupSectorStart = nearestPointAngle - HALF_LOOKUP_SECTOR;
    int lookupSectorEnd = nearestPointAngle + HALF_LOOKUP_SECTOR;

    if (lookupSectorStart < LOOKUP_START_DEG)
    {
      lookupSectorEnd += LOOKUP_START_DEG - lookupSectorStart;
      lookupSectorStart = LOOKUP_START_DEG;
    } else if (lookupSectorEnd > LOOKUP_END_DEG)
    {
      lookupSectorStart -= lookupSectorEnd - LOOKUP_END_DEG;
      lookupSectorEnd = LOOKUP_END_DEG;
    }

    findNearestPoint(lookupSectorStart, lookupSectorEnd, DEG_STEP);
  }

  if (nearestPointDistance <= minDistance)
  {
    bot.speed(0, 0);
    return true; 
  }
  else
  {

    Input = nearestPointAngle;

    if (myPID.Compute())
    {
      int uSpeed = Output;
      int brake = (abs(uSpeed) * 0.8);

      bot.speed(power + uSpeed - brake, power - uSpeed - brake);

    }
    return false;
  }

}

