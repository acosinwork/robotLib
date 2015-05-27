// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------
#define BUZZER                   12

#define P1  11
#define P2  13
#define P3  5
#define P4  6

#define P5  A3
#define P6  A2
#define P7  A1
#define P8  A0

#define P9  8
#define P11 A4
#define P12 A5

#define IR_PIN P12

//I2C-expander IO pins

#define P10 37

//LiquidCrystall
//LCx вид (для LiquidCrystal_I2C.h)
#define LC_ADDR    LCD_TWI_ADDR

#define LC4 0
#define LC5 1
#define LC6 2
#define LC7 3
#define LCEN 4
#define LCRW 5
#define LCRS 6

//Qx вид (для uSerialWrite())
#define Q0 30 //NUM_DIGITAL_PINS 
#define Q1 31
#define Q2 32
#define Q3 33
#define Q4 34
#define Q5 35
#define Q6 36
#define Q7 P10

//LED and Buttons
#define LS0 38
#define LS1 39
#define LS2 40
#define LS3 41

#define LS4 42
#define LS5 43
#define LS6 44
#define LS7 45

//Buttons
#define S1 50
#define S2 51
#define S3 52
#define S4 53
//Leds
#define L1 60
#define L2 61
#define L3 62
#define L4 63

//Motors
#define M1 0
#define M2 1


//#include <Wire.h>
//#include <Strela.h>
#include <NewPing.h>
#include <Servo.h>


Servo myservo;  // create servo object to control a servo
bool rise = false;
int alpha = 0;
int degStep = 1;

#define TRIGGER_PIN  P11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     P12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  myservo.attach(P3);  // attaches the servo on pin 9 to the servo object
  myservo.write(alpha);              // tell servo to go to position in variable 'pos'

}

void loop() {
/*  if (rise)
  {
    alpha += degStep;
    if (alpha >= 180)
      rise = false;
  }
  else
  {
    alpha -= degStep;
    if (alpha <= 0)
      rise = true;
  }

  myservo.write(alpha);
*/  delay(50);             
  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS; // Send ping, get ping time in microseconds (uS).
  static float FK = 0.2;
  static int dist = 0;


  //dist = (1-FK)*dist + FK*uS;
//  for (int i = 0; i < 10; ++i)
//  {
//    delay(30);
    uS = sonar.ping();
   dist = (1-FK)*dist + FK*uS;

    Serial.println(dist/ US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
//  }
}
