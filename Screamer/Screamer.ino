
void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned int val = 0;

  for (int i = 0; i < 4; ++i)
  {
    val += analogRead(A0);
  }
  val >>= 2;

  if (val > 700)
  {
    analogWrite(6, map(analogRead(A0), 0, 1023, 0, 255));
  }
  else
    analogWrite(6, 0);
  Serial.println(analogRead(A0));
}
