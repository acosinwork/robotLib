#include <Wire.h>
#include <Strela.h>


#include <DistanceGP2Y0A21YK.h>
DistanceGP2Y0A21YK Dist;
int distance;
void setup()
{
Serial.begin(9600);
Dist.begin(P9);
}
void loop()
{
distance = Dist.getDistanceCentimeter();
Serial.print("\nDistance in centimers: ");
Serial.print(distance);
//delay(500); //make it readable
}
