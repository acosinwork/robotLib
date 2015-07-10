#include "Buttons.h"

#define BUTTON_TIMEOUT_CHECK 10


uint8_t Buttons::check()
{
  if (_checkFQ.timeout(BUTTON_TIMEOUT_CHECK)) {

    uint8_t measureNum = ++_buttonCheckCounter % BUTTONS_MEASURE_COUNT;
    _lastButtonState[measureNum] = buttonsState();

    uint8_t pressed, released;

    pressed = released = _lastButtonState[measureNum];

    for (uint8_t i = 0; i < BUTTONS_MEASURE_COUNT; ++i)
    {
      pressed &= _lastButtonState[i];
      released |= _lastButtonState[i];
    }
    _lastFilteredState = _currentFiltredState;
    _currentFiltredState = pressed & released;

        // something wrong (maybe bad):
//TODO
    uint8_t stateChanges = _lastFilteredState ^ _currentFiltredState;
        // get all changes from 0 to 1
    _newPress = stateChanges & (~_lastFilteredState);
        //get all changes from 1 to 0
    _newRelease = stateChanges & (~_currentFiltredState);

      //это как-то можно сделать через массив

    if (_newPress & _pressCalbackAttached & _BV(0))
      pressCallbackS1();

    if (_newPress & _pressCalbackAttached & _BV(1))
      pressCallbackS2();

    if (_newPress & _pressCalbackAttached & _BV(2))
      pressCallbackS3();

    if (_newPress & _pressCalbackAttached & _BV(3))
      pressCallbackS4();

      // И это тоже можно как-то через массив

    if (_newRelease & _releaseCalbackAttached & _BV(0))
      releaseCallbackS1();

    if (_newRelease & _releaseCalbackAttached & _BV(1))
      releaseCallbackS2();

    if (_newRelease & _releaseCalbackAttached & _BV(2))
      releaseCallbackS3();

    if (_newRelease & _releaseCalbackAttached & _BV(3))
      releaseCallbackS4();


  }
  return _currentFiltredState;
}

void Buttons::onPress(uint8_t button, void (*callback)())
{

  uint8_t butNum = button - S1;

  if ((butNum >=0) && (butNum < 4))
  {

    _pressCalbackAttached |= 1<<butNum;

    switch (button)
    {
      case S1:
      pressCallbackS1 = callback;
      break;
      case S2:
      pressCallbackS2 = callback;
      break;
      case S3:
      pressCallbackS3 = callback;
      break;
      case S4:
      pressCallbackS4 = callback;
      break;       
    }
  }
}

void Buttons::onRelease(uint8_t button, void (*callback)())
{

  uint8_t butNum = button - S1;

  if ((butNum >=0) && (butNum < 4))
  {

    _releaseCalbackAttached |= 1<<butNum;

    switch (button)
    {
      case S1:
      releaseCallbackS1 = callback;
      break;
      case S2:
      releaseCallbackS2 = callback;
      break;
      case S3:
      releaseCallbackS3 = callback;
      break;
      case S4:
      releaseCallbackS4 = callback;
      break;       
    }
  }
}

uint8_t Buttons::getState()
{
  return _currentFiltredState;
}
