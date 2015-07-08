#include <inttypes.h>
#include <Arduino.h>
#include <Wire.h>
#include <Strela.h>


class PinManager
{
public:

	void turnOn(uint8_t pin)
	{
		uPinMode(pin, OUTPUT);
		uDigitalWrite(pin, HIGH);
	}

	void turnOff(uint8_t pin)
	{
		uPinMode(pin, OUTPUT);
		uDigitalWrite(pin, LOW);
	}

	void beep(int freq, int length)
	{
		tone(BUZZER, freq, length);
	}

	bool isHigh(uint8_t pin)
	{
		uPinMode(pin, INPUT);
		return uDigitalRead(pin);
	}

	bool isLow(uint8_t pin)
	{
		uPinMode(pin, INPUT);
		return !uDigitalRead(pin);
	}
	
};