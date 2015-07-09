#include <Wire.h>
#include <Strela.h>
#include <inttypes.h>
#include "Amp_ino.h"

#define BUTTON_TIMEOUT_CHECK 10
#define MEASURE_COUNT 3


class Buttons{
public:
  void check()
  {
    if (_checkFQ.timeout(BUTTON_TIMEOUT_CHECK)) {

    	uint8_t measureNum = ++_buttonCheckCounter % MEASURE_COUNT;
        _lastButtonState[measureNum] = buttonsState();

        uint8_t pressed, released;

        pressed = released = _lastButtonState[measureNum];

        for (uint8_t i = 0; i < MEASURE_COUNT; ++i)
        {
        	pressed &= _lastButtonState[i];
        	released |= _lastButtonState[i];
        }
        _currentFiltredState = pressed & released;
    }
  }

  uint8_t getState()
  {
  	check();
  	return _currentFiltredState;
  }

private:

  TimeOut _checkFQ;
  uint8_t _buttonCheckCounter;
  uint8_t _lastButtonState[MEASURE_COUNT];
  uint8_t _currentFiltredState;

};
