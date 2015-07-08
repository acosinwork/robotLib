
#include <Wire.h>
#include <Strela.h>

//#define SERIAL_TX_BUFFER_SIZE 512

#include "ascii-art.h"
String s[] = {
  "  _    _      _ _         __     __       _           _ ",
  " | |  | |    | | |        \\ \\   / /      | |         | |",
  " | |__| | ___| | | ___     \\ \\_/ /_ _ ___| |__   __ _| |",
  " |  __  |/ _ \\ | |/ _ \\     \\   / _` / __| '_ \\ / _` | |",
  " | |  | |  __/ | | (_) |     | | (_| \\__ \\ | | | (_| |_|",
  " |_|  |_|\\___|_|_|\\___( )    |_|\\__,_|___/_| |_|\\__,_(_)",
  " \\ \\        / /       |/                                ",
  "  \\ \\  /\\  / /__                                        ",
  "    \\  /\\  /  __/                                       ",
  "     \\/  \\/ \\___|                                       "
};

VideoBuffer video;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (uDigitalRead(S2))
    video.movePos( -1);
  
  
  if (uDigitalRead(S4))
    video.movePos( 1);
  for (int i=0; i< DEF_COLUMNS; ++i)
  {  
    video.buf[i][DEF_ROWS-1] = video.blank;
  }
  video.buf[video.pos][DEF_ROWS-1] = video.gamer;
    


  for (int row = 0; row < DEF_ROWS; ++row)
  {
    for (int col = 0; col < DEF_COLUMNS; ++col)
    {
      Serial.print(video.buf[col][row]);
    }
    Serial.println();
  }
  delay(120);
}
