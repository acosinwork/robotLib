#include <Wire.h>
#include <Strela.h>
#include <inttypes.h>
#include "Amp_ino.h"

#define BUTTONS_MEASURE_COUNT 3

class Buttons{
public:

  uint8_t check();
  
  void onPress(uint8_t button, void (*callback)());

  void onRelease(uint8_t button, void (*callback)());

  uint8_t getState();

  void (*pressCallbackS1)();
  void (*pressCallbackS2)();
  void (*pressCallbackS3)();
  void (*pressCallbackS4)();

  void (*releaseCallbackS1)();
  void (*releaseCallbackS2)();
  void (*releaseCallbackS3)();
  void (*releaseCallbackS4)();

private:

  TimeOut _checkFQ;
  uint8_t _buttonCheckCounter;
  uint8_t _lastButtonState[BUTTONS_MEASURE_COUNT];
  uint8_t _currentFiltredState;
  uint8_t _lastFilteredState;
  uint8_t _newPress;
  uint8_t _newRelease;

  uint8_t _pressCalbackAttached = 0;
  uint8_t _releaseCalbackAttached = 0;


};
