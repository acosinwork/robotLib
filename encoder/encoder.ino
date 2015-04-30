#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <LineBot.h>
#include <LiquidCrystal_I2C.h>
#include <PID_v1.h>

unsigned long timetimetime = 0;

int leftStep = 0, rightStep = 0;

int power = 150;//90;

const double multiplier = 3.0 / 1024;
double Setpoint, Input, Output;

double Kp = 1.14, Ki = 0.4, Kd = 0.08;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


LineBot bot;

LiquidCrystal_I2C lcd(LC_ADDR, LCEN, LCRW, LCRS, LC4, LC5, LC6, LC7);

void setup() {
  // put your setup code here, to run once:

  bot.begin();
  bot.sensors.attach(P6);
  bot.sensors.attach(P7);

  //Инициализация экрана. У нашего экрана 8 символов 2 строки
  lcd.begin(8, 2);
  //Переместим курсор в начало первой стройки (символ 0, строка 0)
  lcd.home();

  bot.speed(50, 50);

}

void loop() {

  if (millis() - timetimetime > 50)
  {

    timetimetime = millis();
    lcd.clear();
    lcd.home();
    lcd.print("L=");
    lcd.print(leftStep);
    lcd.setCursor(0, 1);
    lcd.print("R=");
    lcd.print(rightStep);

  }
  
  readWheel();

  // put your main code here, to run repeatedly:
  /*
    Input = getLine();
    if (myPID.Compute())
    {
  //    lcd.home();
  //    lcd.print(millis() - timetimetime);
  //    timetimetime = millis();

      int uSpeed = Output;
      int brake = (abs(uSpeed)>>1);

      bot.speed(power - uSpeed - brake, power + uSpeed - brake);
    }
    checkClick();
  */

}

void readWheel()
{
  static bool left = false, right = false;
  bool nowLeft = digitalRead(P8);
  bool nowRight = digitalRead(P4);

  if (!left && nowLeft)
    ++leftStep;

  if (!right && nowRight)
    ++rightStep;

  left = nowLeft;
  right = nowRight;


}
