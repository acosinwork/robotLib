#include <Wire.h>
#include <Strela.h>
#include <inttypes.h>
#include "libraries/Robot/utility/Amp_ino.h"

#define BUTTON_TIMEOUT_CHECK 10

class Buttons{
public:
  void check()
  {
    if (_checkFQ.timeout(BUTTON_TIMEOUT_CHECK)) {
      _lastButtonState &= buttonsState();

    }
  }

private:

  TimeOut _checkFQ;
  int _buttonCheckCounter=3;
  uint8_t _lastButtonState = 0x0f;

};
/*
uint8_t button()
{
  uint8_t butto
  if (buttonCheck.timeout(10)) {
  }

  buttonsState();
}
*/
