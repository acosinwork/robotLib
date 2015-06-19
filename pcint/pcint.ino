#include <EEPROM.h>
#include <Wire.h>
#include <Strela.h>
#include <LineBot.h>
#include <PID_v1.h>
#include <Amp_ino.h>
#include <Servo.h>



#include <PinChangeInt.h>

#define ENC_R 11
#define ENC_L 8

volatile long interrupt_count[2]={0}; // possible arduino pins

int power = 60;

double Setpoint, Input, Output;

double Kp = 1.5, Ki = 0.8, Kd = 0.02;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


LineBot bot;


void quicfunc0() {
  interrupt_count[0]++;
};

void quicfunc1() {
  interrupt_count[1]++;
};

void setup() {
    bot.begin();
    
  Setpoint = 0;

  attachPinChangeInterrupt(ENC_L, quicfunc0, FALLING);

  attachPinChangeInterrupt(ENC_R, quicfunc1, FALLING);


  Serial.begin(115200);
  
    myPID.SetOutputLimits(-power, power);

  myPID.SetMode(AUTOMATIC);

}

void loop() {

  Serial.println(Input = interrupt_count[1] - interrupt_count[0]);
  if (myPID.Compute())
  {
    int uSpeed = Output;

    bot.speed(power - uSpeed, power + uSpeed);
  }

  
}

