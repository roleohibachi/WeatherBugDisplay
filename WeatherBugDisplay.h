/*
 * WeatherBugDisplay.h - AWS/WeatherBug Display TTL Serial protocol
 *
 * By Mike Seery
 *
 * Project URL: https://hackaday.io/project/28535-awsweatherbug-display-resurrection
 *
 */

#ifndef WeatherBugDisplay_H
#define WeatherBugDisplay_H

#include "Arduino.h"
#include <SoftwareSerial.h>

class WeatherBugDisplay
{
  public:
	WeatherBugDisplay(SoftwareSerial *ser); // Constructor when using SoftwareSerial
	WeatherBugDisplay(HardwareSerial *ser); // Constructor when using HardwareSerial
	
	void update();
	void setTime();
	
  private:
	SoftwareSerial *_swSerial;
	HardwareSerial *_hwSerial;
	uint8_t* _data[];


};

#endif
