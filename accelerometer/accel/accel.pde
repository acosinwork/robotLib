
import processing.serial.*;
Serial port;

String s = new String("no data");

String f = new String("no data");;
String sec = new String("no data");;
String t = new String("no data");;
 

float[] coord = new float[3];

void setup()
{
  size(500, 500);
  port = new Serial(this, "COM4", 115200);
  port.bufferUntil('\n');  


}

void draw()
{
  background(0);
  stroke(255);
  
  text(s, 10, 30);
  

}
  
void serialEvent (Serial port)
{
  try {
  s = port.readStringUntil('\n');

  
  int first = s.indexOf(',');
  int second = s.indexOf(',', first+1);
  int third = s.indexOf(',', second+1);
  
  f = s.substring(0, first);
  sec = s.substring(first+1, second);
  t = s.substring(second+1,s.length()-1);

  coord[0] = float(f);
  coord[1] = float(sec);
  coord[2] = float(t);
  
  
//  s= nextValue + " V";

  } catch (Exception e) {
    println("Connection...");
  }
   
}

void stop() {
  port.clear();
  port.stop();
} 