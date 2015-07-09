#include <Arduino.h>
#include <inttypes.h>

#define DEF_COLUMNS 16
#define DEF_ROWS    8


class VideoBuffer
{
  public:
  
  void movePos(int moveMe)
  {
    int newPosition = pos + moveMe;
    if ((newPosition < DEF_COLUMNS) && (newPosition>-1))
    pos += moveMe;
  }
  
  
  
  char buf[DEF_COLUMNS][DEF_ROWS];
  
  char gamer = 'A';
  char inwaderBig = 'W';
  char inwaderSmall = 'O';
  char blank = ' ';
  byte pos= DEF_COLUMNS/2;
  
  

};


