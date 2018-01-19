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
#include <Time.h>

class WeatherBugDisplay
{
  public:
  WeatherBugDisplay(SoftwareSerial *ser);
  WeatherBugDisplay(HardwareSerial *ser);
  void update() ;
  void setTime(time_t t) ;
  void setTempsF(float ind, float out, float aux);
  void setTempsC(float ind, float out, float aux);
  void setBaro(float inhg, float rate);
  void setHumidity(float percent);
  void setRainInches(float day, month, year);
  void setWind(float kmhr, int dir, float avgkmhr, int avgdir);

  private:
  SoftwareSerial *_swSerial;
  HardwareSerial *_hwSerial;
  size_t _xmit(const char str[]);
  size_t _xmit(char c);
  size_t _xmit(uint16_t n);
  size_t _xmit(unsigned long n);
  size_t _xmitln(void) ;
  size_t _xmitln(const char c[]) ;
  size_t _xmitln(char c);
  
  uint16_t _hours;
  uint16_t _minutes;
  uint16_t _month;
  uint16_t _day;
  uint16_t _indtemp;
  uint16_t _outtemp;
  uint16_t _auxtemp;
  uint16_t _humidity;
  uint16_t _baropress;
  uint16_t _dailyrain;
  uint16_t _monthlyrain;
  uint16_t _yearlyrain;
  uint16_t _windvel;
  uint16_t _winddir;
  uint16_t _avgwindvel;
  uint16_t _avgwinddir;
  uint16_t _barorate;
	
#endif
