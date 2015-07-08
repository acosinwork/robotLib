#ifndef SUMOBOT_H
#define SUMOBOT_H

#include <inttypes.h>
#include "Robot.h"

#include <utility/LineSensor.h>
//#include <utility/Ultrasonic/Ultrasonic.h>

#include <utility/UltrasonicScan.h>

#include <utility/PinManager.h>

class SumoBot : public Robot
{
	public:
		SumoBot();

		void begin();

		LineSensor sensors;

		UltrasonicScaner head;

		Melody voice;

		PinManager pin;


		

};

#endif