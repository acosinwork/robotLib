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
#define HALF_LOOKUP_SECTOR   15//20


enum State {
  FIND_THE_WALL,
  GET_WALL_POSITION,
  FOLLOW_THE_WALL
} state;


int nearestPointAngle, nearestPointDistance;
int oldDist = 0;

int power = 80;//50;

int needDistance = 40;

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

  state = FIND_THE_WALL;

  lookThis(LOOKUP_START_DEG);

  int nearestPointDistance = 20000; // максимум короче

  while (nearestPointDistance != getDistanceCentimeter())
  {
    delay(100);
    nearestPointDistance = getDistanceCentimeter();
  }

  myPID.SetSampleTime(30);
  myPID.SetOutputLimits(-power, power);

  myPID.SetMode(AUTOMATIC);



}

void loop() {
  // put your main code here, to run repeatedly:

  switch (state)
  {
    case FIND_THE_WALL:

      uDigitalWrite(L1, HIGH);
      uDigitalWrite(L2, LOW);
      uDigitalWrite(L3, LOW);


      if (findTheWall(needDistance * 1.2))
        state = GET_WALL_POSITION;
      break;

    case GET_WALL_POSITION:


      uDigitalWrite(L1, LOW);
      uDigitalWrite(L2, HIGH);
      uDigitalWrite(L3, LOW);

      if (getWallPosition())
        state = FOLLOW_THE_WALL;
      myPID.SetTunings(0.9, 0.2, 0.01);
      break;

    case FOLLOW_THE_WALL:


      uDigitalWrite(L1, LOW);
      uDigitalWrite(L2, LOW);
      uDigitalWrite(L3, HIGH);

      if (!followTheWall())
        state = FIND_THE_WALL;
      myPID.SetTunings(0.1, 0.0, 0.0);
      break;
  }


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
      delay(abs(measures[i][angle] - nearestPointAngle) * 2);

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


void lookup()
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
}


bool findTheWall(int minDistance)
{
  lookup();

  if (nearestPointDistance <= minDistance)
  {
    bot.speed(0, 0);
    return true;
  }

  Input = nearestPointAngle;

  if (myPID.Compute())
  {
    int uSpeed = Output;
    int brake = (abs(uSpeed) * 0.8);

    bot.speed(power + uSpeed - brake, power - uSpeed - brake);

  }
  return false;
}

bool getWallPosition()
{
  if ((nearestPointAngle - HALF_LOOKUP_SECTOR) > LOOKUP_START_DEG)
  {
    bot.speed(-power, power);
    delay(200);
    bot.speed(0, 0);
    lookup();
    return false;
  }
  else
    return true;
}

bool followTheWall()
{

  lookup();

  //  if (nearestPointDistance > 2 * needDistance)
  //    return false;

  if ((nearestPointAngle < HALF_LOOKUP_SECTOR) && (nearestPointAngle > -HALF_LOOKUP_SECTOR) && (nearestPointDistance < needDistance))
  {
    bot.speed(-power, -power);

    delay(200);
    return false;
  }
  else
  {

    if (nearestPointAngle < 0 - HALF_LOOKUP_SECTOR)
      Input = nearestPointDistance - needDistance - needDistance * cos(nearestPointAngle * PI / 180);

    else if (nearestPointAngle > 0 + HALF_LOOKUP_SECTOR)

      Input = nearestPointDistance + needDistance + needDistance * cos(nearestPointAngle * PI / 180);

    if (myPID.Compute())
    {
      int uSpeed = Output;
      int brake = (abs(uSpeed) >> 1);

      bot.speed(power - uSpeed - brake, power + uSpeed - brake);
    }

  }
  return true;

}


