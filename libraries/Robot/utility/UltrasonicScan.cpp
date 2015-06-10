#include "UltrasonicScan.h"

#define ULTRASONIC_MEASURE_TIMEOUT 25UL

#define MIN_ANGLE -90
#define MAX_ANGLE 90


///////////////
UltrasonicTimeout::UltrasonicTimeout(int trigPin, int echoPin, long timeout) : Ultrasonic(trigPin, echoPin)
{
	setTimeout(timeout);
}

UltrasonicTimeout::UltrasonicTimeout(int trigPin, int echoPin) : Ultrasonic(trigPin, echoPin)
{
	setTimeout(15000); // ~2.5 m
}

	void UltrasonicTimeout::setTimeout(long timeout)
{
	_timeout = timeout;
}


long UltrasonicTimeout::timing()
{
	digitalWrite(_trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(_trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(_trigPin, LOW);
	return pulseIn(_EchoPin, HIGH, _timeout); 
}

///////////////

void UltrasonicFiltered::setKF(float k_filter)
{
	_firstMeasure = true;
	_kFilt = k_filter;
}

float UltrasonicFiltered::getRawDistance()
{
	if (long timingIsCorrect = timing())
		return CalcDistance(timingIsCorrect, CM);
	else
		return _oldDistance;
}

float UltrasonicFiltered::getDistance()
{

	if (_firstMeasure) {
		_oldDistance = getRawDistance();
		_firstMeasure = false;
	}
	else if (_betweenMeasurements.timeout(ULTRASONIC_MEASURE_TIMEOUT))
	{
		_oldDistance = (1.0 - _kFilt) * _oldDistance + _kFilt * getRawDistance();
	}

	return _oldDistance;
}

////////////////

    UltrasonicScaner::UltrasonicScaner()
    {
    	_sectorStart = MIN_ANGLE;
    	_sectorEnd = MAX_ANGLE;
    }

	void UltrasonicScaner::attachUltrasonic(int trigPin, int echoPin)
	{
		ultrasonic = new UltrasonicFiltered(trigPin, echoPin);
	}

	void UltrasonicScaner::attachServo(int servoPin)
	{
		servo.attach(servoPin);
		lookAt(0);
	}

	void UltrasonicScaner::lookAt(int angle)
	{
		constrain(angle, MIN_ANGLE, MAX_ANGLE);
		_currentAngle = angle;
		servo.write(angle + 90);
	}

	float UltrasonicScaner::getDistance()
	{
		return ultrasonic->getDistance();
	}

	int UltrasonicScaner::getAngle()
	{
		return _currentAngle;
	}

	void UltrasonicScaner::setLookUpSector(int fromAngle, int toAngle)
	{
		if (fromAngle < toAngle)
		{
			_sectorStart = fromAngle;
			_sectorEnd = toAngle;
		}
		else
		{
			_sectorStart = toAngle;
			_sectorEnd = fromAngle;
		}

		int rightArcAngle = abs(_currentAngle - _sectorStart);
		int leftArcAngle = abs(_currentAngle - _sectorEnd);

		if (rightArcAngle < leftArcAngle)
			_servoState = clockwise;
		else
			_servoState = counterclockwise;
		
		/*
		if (_currentAngle <= _sectorStart)
			_servoState = counterclockwise;
		else if (_currentAngle >= _sectorEnd)
			_servoState = clockwise;

//deleteit
		_servoState = clockwise;
		*/

	}

bool UltrasonicScaner::findNearestPointAngle()
{		
	bool result = false;

	if (sweep.timeout(ULTRASONIC_MEASURE_TIMEOUT))
	{			
		switch (_servoState)
		{
			case wait:
			{
				result = true;
			}
			break;

			case clockwise:
			{
				if (_currentAngle > _sectorStart)
					lookAt(_currentAngle - 1);
				else
					_servoState = counterclockwise;
			}
			break;

			case counterclockwise:
			{
				if (_currentAngle < _sectorEnd)
					lookAt(_currentAngle + 1);
				else
					_servoState = clockwise;
			}
			break;

		}
	}
	return result;
}
