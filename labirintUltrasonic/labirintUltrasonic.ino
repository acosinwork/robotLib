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

unsigned long timetimetime = 0;

unsigned long timeServo = 0;

unsigned long timeUltra = 0;


int needDistance = 40;

int alpha = 10;
int degStep = 10;

bool rise = true;

int power = 50;

const double multiplier = 3.0 / 1024;
double Setpoint, Input, Output;

double Kp = 1.14, Ki = 0.4, Kd = 0.08;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


LineBot bot;

LiquidCrystal_I2C lcd(LC_ADDR, LCEN, LCRW, LCRS, LC4, LC5, LC6, LC7);

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

void setup() {
  // put your setup code here, to run once:

  myservo.attach(P3);  // attaches the servo on pin 9 to the servo object
  myservo.write(alpha);              // tell servo to go to position in variable 'pos'

  bot.begin();
  bot.sensors.attach(P9);
  //  bot.sensors.attach(P7);

  //Инициализация экрана. У нашего экрана 8 символов 2 строки
  lcd.begin(8, 2);
  //Переместим курсор в начало первой стройки (символ 0, строка 0)
  lcd.home();

  printAll();


  Input =  getDistanceCentimeter() - needDistance;
  Setpoint = 0;

  delay(1000);
  //turn the PID on
  myPID.SetSampleTime(100);
  myPID.SetOutputLimits(-power, power);

  myPID.SetMode(AUTOMATIC);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (millis()-timeUltra > 10)
  {
  Input =  getDistanceCentimeter() * cos(alpha*PI/180) - needDistance;
  timeUltra=millis();
  }

  if (millis()-timeServo > 100)
  {
    if (rise)
    {
      alpha += degStep;
      if (alpha >= 60)
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


  if (myPID.Compute())
  {
    //    lcd.home();
    //    lcd.print(millis() - timetimetime);
    //    timetimetime = millis();

    int uSpeed = Output;
    int brake = (abs(uSpeed) >> 1);

    bot.speed(power - uSpeed - brake, power + uSpeed - brake);
  }
  checkClick();

}

int getDistanceRaw()
{
  return bot.sensors.read(0);//(bot.sensors.readPct(0) - bot.sensors.readPct(1));
}

bool checkClick()
{


  static bool lastClick = false;
  static unsigned long time = 0;
  if (millis() - time >= 50)
  {
    bool result = uDigitalRead(S1);
    if (!lastClick && result) {

      while (uDigitalRead(S1))
        delay(10);


      tone(BUZZER, 1000, 50);
      bot.speed(0);



      bool pressed = false;
      while (!pressed)
      {
        if ((millis() % 50) > 40)
        {
          lcd.clear();
          lcd.home();
          lcd.print(setK());
        }

        if (uDigitalRead(S2))
        {
          pressed = true;
          Kp = setK();
        } else if (uDigitalRead(S3))
        {
          pressed = true;
          Ki = setK();
        } else if (uDigitalRead(S4))
        {
          pressed = true;
          Kd = setK();
        }
        else if (uDigitalRead(S1))
        {
          pressed = true;
        }
      }

      myPID.SetTunings(Kp, Ki, Kd);

      // reinitialize PID
      //      myPID.SetMode(MANUAL);
      //      myPID.SetMode(AUTOMATIC);


      printAll();
      delay(3000);
    }
    time = millis();
    lastClick = result;
  }
  return lastClick;
}


void printAll()
{
  lcd.clear();
  lcd.home();
  lcd.print(myPID.GetKp());
  lcd.print(myPID.GetKi());
  lcd.setCursor(0, 1);
  lcd.print(myPID.GetKd());
}

double setK()
{
  return (double)analogRead(P9) * multiplier;
}
/*
int getDistanceCentimeter()
{
  int adcValue = getDistanceRaw();
  if (adcValue > 600)                             // lower boundary: 4 cm (3 cm means under the boundary)
  {
    return (3);
  }

  if (adcValue < 80 )                             //upper boundary: 36 cm (returning 37 means over the boundary)
  {
    return (37);
  }

  else
  {
    return (1 / (0.0002391473 * adcValue - 0.0100251467));
  }
}
*/
double getDistanceCentimeter()
{
  static long lastMicros = 0;
  long microsec = ultrasonic.timing();
  
  if (microsec>8000)
   microsec = lastMicros;
   else
   lastMicros = microsec;

  return ultrasonic.CalcDistance(microsec, Ultrasonic::CM); //this result unit is centimeter
}


