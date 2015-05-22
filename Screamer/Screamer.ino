// Кричалка
#define LED_PIN 10
#define MICROPHONE_PIN A5

void setup() {
  //Светодиод
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  unsigned int val = 0;

  for (int i = 0; i < 4; ++i)
  {
    val += analogRead(MICROPHONE_PIN);
  }
  val >>= 2;

  if (val > 700)
  {
    analogWrite(LED_PIN, map(analogRead(MICROPHONE_PIN), 0, 1023, 0, 255));
  }
  else
    analogWrite(LED_PIN, 0);
  Serial.println(analogRead(MICROPHONE_PIN));
}
