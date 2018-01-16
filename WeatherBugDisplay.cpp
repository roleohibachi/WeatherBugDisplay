/*
 * WeatherBugDisplay.cpp - AWS/WeatherBug Display TTL Serial protocol
 *
 * By Mike Seery
 *
 * Project URL: https://hackaday.io/project/28535-awsweatherbug-display-resurrection
 *
 */

#include "Arduino.h"
#include "WeatherBugDisplay.h"
//#include <Time.h>

#define datalen 36

uint8_t* _data[datalen] = {
  "\x0A",		//START
  "00\xAC",		//hours, 24-hr format. If >12, add 12. "111\xAC"=99.
  "00xAC",		//Minutes, max 99. 
  "00\xAC",		//First field (US month)
  "00\xAC",		//Second field (US day)
  "01744\xAC",	//ind temp. x = 1000 * (25*F + 368) / 211​ = 1000 * (45*C + 1168) / 211
  "01744\xAC",	//outside temp
  "01744\xAC",	//aux temp
  "979\xAC",	//unknown
  "4439\xAC",	//humidity
  
  /* TODO finish characterizing humidity
  "0000"-"0300"=75-100%
  "0301"-"0999"=100%
  Everything else is 0%
  */
  
  "0\xAC",    	//unknown
  "07647\xAC",  //barometer
  "0\xAC",    	//unknown
  "65535\xAC",  //daily rainfall, hundredths of an inch. Max "65535\xAC" = 655.35in
  "00000\xAC",  //monthly rainfall
  "00000\xAC",  //yearly rainfall
  "000\xAC",  	//speed in km/hr. (display only has 2 digits, but truncates >99)
  "00\xAC",   	//Wind direction. 15 LEDs, indexed clockwise. W=12. Wraps around. ESE lights two LEDs?!
  "0\xAC",    	//??
  "00\xAC",   	//Avg wind speed
  "09\xAC",   	//avg wind direction
  "53\xAC",   	//unk
  "0\xAC",    	//unk
  "0\xAC",    	//unk
  "65000\xAC",  //baro rate, also rising/falling LEDs
  
  //TODO finish characterizing. So far I know:
  /*
    0 0
    20000 5.23
    30000 7.84
    32000 8.37
    32500 8.5
    32900 -1.53
    34000 -1.24
    44000 -1.63
    64000 -0.4
  */
  
  "0\xAC",		//unk
  "0\xAC",		//unk
  "0\xAC",		//unk
  "0\xAC",		//unk
  "0\xAC",		//unk
  "0\xAC",		//unk
  "0\xAC",		//unk
  "0\xAC",		//unk
  "0\xAC",		//unk
  "0\xAC",		//unk
  "\x8D"		//EOM
};

// Constructor when using SoftwareSerial or NewSoftSerial
WeatherBugDisplay::WeatherBugDisplay(SoftwareSerial *ser) {
	_swSerial = ser; 
	_swSerial->begin(9600);
}

// Constructor when using HardwareSerial
WeatherBugDisplay::WeatherBugDisplay(HardwareSerial *ser) {
	_hwSerial = ser; 
	_hwSerial->begin(9600);
}

void WeatherBugDisplay::update(){
	if(_swSerial) {
		for (int i = 0; i < datalen; i++) {
			//_swSerial->print(_data[i]);
			_swSerial->print(0xAC);
		}
	}else{
		for (int i = 0; i < datalen; i++) {
			//_hwSerial->print(_data[i]);
			_hwSerial->print(0xAC);
		}
	}
}

void WeatherBugDisplay::setTime(){
	
	// char buf[3];
	// itoa(hour(), buf, 10);
	// buf[2] = 0xAC;
	
	_data[1] = "12\xAC";//TODO hours go here	
	_data[2] = "34\xAC";//TODO mins go here
	_data[3] = "56\xAC";//TODO Month goes here
	_data[4] = "78\xAC";//TODO hours go here
	
}