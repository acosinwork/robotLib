/**
 * RGB Cube.
 * 
 * The three primary colors of the additive color model are red, green, and blue.
 * This RGB color cube displays smooth transitions between these colors. 
 */


import processing.serial.*;
Serial port;

String s = new String("no data");

String f = new String("no data");

String sec = new String("no data");

String t = new String("no data");



float[] coord = new float[3];

float xmag, ymag = 0;
float newXmag, newYmag = 0; 

void setup() { 
  size(640, 360, P3D); 
  noStroke(); 
  colorMode(RGB, 1); 

  port = new Serial(this, "COM4", 115200);
  port.bufferUntil('\n');
} 

void draw() { 
  background(0.5);
  
  text(s, 10, 30);

  pushMatrix(); 
  translate(width/2, height/2, -30); 

  newXmag = (width*coord[0]/9.8)/float(width*4) * TWO_PI;
  newYmag = (height*coord[1]/9.8)/float(height*4) * TWO_PI;

  float diff = xmag-newXmag;
  if (abs(diff) >  0.01) { 
    xmag -= diff/4.0;
  }

  diff = ymag-newYmag;
  if (abs(diff) >  0.01) { 
    ymag -= diff/4.0;
  }

  rotateX(-ymag); 
  rotateY(-xmag); 

  scale(90);
  beginShape(QUADS);

  fill(0, 1, 1); 
  vertex(-1, 1, 1);
  fill(1, 1, 1); 
  vertex( 1, 1, 1);
  fill(1, 0, 1); 
  vertex( 1, -1, 1);
  fill(0, 0, 1); 
  vertex(-1, -1, 1);

  fill(1, 1, 1); 
  vertex( 1, 1, 1);
  fill(1, 1, 0); 
  vertex( 1, 1, -1);
  fill(1, 0, 0); 
  vertex( 1, -1, -1);
  fill(1, 0, 1); 
  vertex( 1, -1, 1);

  fill(1, 1, 0); 
  vertex( 1, 1, -1);
  fill(0, 1, 0); 
  vertex(-1, 1, -1);
  fill(0, 0, 0); 
  vertex(-1, -1, -1);
  fill(1, 0, 0); 
  vertex( 1, -1, -1);

  fill(0, 1, 0); 
  vertex(-1, 1, -1);
  fill(0, 1, 1); 
  vertex(-1, 1, 1);
  fill(0, 0, 1); 
  vertex(-1, -1, 1);
  fill(0, 0, 0); 
  vertex(-1, -1, -1);

  fill(0, 1, 0); 
  vertex(-1, 1, -1);
  fill(1, 1, 0); 
  vertex( 1, 1, -1);
  fill(1, 1, 1); 
  vertex( 1, 1, 1);
  fill(0, 1, 1); 
  vertex(-1, 1, 1);

  fill(0, 0, 0); 
  vertex(-1, -1, -1);
  fill(1, 0, 0); 
  vertex( 1, -1, -1);
  fill(1, 0, 1); 
  vertex( 1, -1, 1);
  fill(0, 0, 1); 
  vertex(-1, -1, 1);

  endShape();

  popMatrix();
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