
#ifndef _ULTRASONIC_SCAN_H_
#define _ULTRASONIC_SCAN_H_

#include <Arduino.h>
#include "Ultrasonic.h"
#include "Amp_ino.h"
#include <Servo.h>
 
class UltrasonicTimeout : public Ultrasonic
{
public:
	UltrasonicTimeout(int trigPin, int echoPin, long timeout);

	UltrasonicTimeout(int trigPin, int echoPin);

	void setTimeout(long timeout);

	long timing();

private:

	long _timeout;
};


class UltrasonicFiltered : public UltrasonicTimeout
{
public:

	UltrasonicFiltered(int trigPin, int echoPin) : UltrasonicTimeout(trigPin, echoPin){}

    void setKF(float k_filter);
	float getRawDistance();
	float getDistance();

private:
	float _kFilt = 0.25;
	float _oldDistance = 0;
	bool _firstMeasure = true;
	TimeOut _betweenMeasurements;
};

class UltrasonicScaner
{
public:
	
	UltrasonicScaner();
	void attachUltrasonic(int trigPin, int echoPin);
	void attachServo(int servoPin);

	void lookAt(int angle);

	float getDistance();
	int getAngle();
	

	void setLookUpSector(int fromAngle, int toAngle);


	bool findNearestPointAngle();

	
private:
	Servo servo;
	UltrasonicFiltered* ultrasonic;

    int _sectorStart;
    int _sectorEnd;

	enum ServoState {
		wait,
		clockwise,
		counterclockwise
	} _servoState;

	int _currentAngle;

//	bool _clockWiseRotation = true;
//	bool _seek = false;


	TimeOut sweep;

};


#endif