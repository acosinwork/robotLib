#include <Wire.h>
#include <lis331dlh.h>

LIS331DLH_TWI accel;
void setup() {
  // put your setup code here, to run once:
accel.begin();
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(accel.readX_G(),2);


delay(100);


}


