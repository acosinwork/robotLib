/*
 *Ultrasonic.h - Library for HC-SR04 Ultrasonic sensor module
 *@Author:draon
 *@DATA:2013-8-7
 *Company website:www.elecfreaks.com
 */
#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

#include <stddef.h>
#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#else
	#include <Wprogram.h>
#endif

class Ultrasonic
{
	public:
		/*
		 *@param tp:trigger pin
		 *@param ep:echo pin
		 */
		Ultrasonic(int tp,int ep);
		long timing();//return Ultrasonic sensor send and receive total time
		/*
		 *@param microsec:Ultrasonic sensor send and receive total time
	 	 *@param metric:the value decide return value is Centimeters or inches
	 	 *@return calculate distance
		 */ 
		float CalcDistance(long microsec,int metric);
		/*
		 *@param value:modify divisor value
		 *@param metric:judge set value is Centimeters divisor value or inches divisor value
		 */
		void SetDivisor(float value,int metric);
		static const int CM = 1;
		static const int IN = 0;
	private:
		int _trigPin;//Trigger Pin
		int _EchoPin;//Echo Pin
		float _cmDivisor;//centimeter divisor parameter
		float _inDivisor;//Inches divisor parameter
		
};
#endif