#define MOTOR 9
#define POT A0
#define AUDIO A5

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
digitalWrite(13, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

analogWrite(MOTOR, (analogRead(POT)>>2));
Serial.println(analogRead(AUDIO));

}
