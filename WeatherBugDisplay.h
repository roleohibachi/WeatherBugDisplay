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
  uint8_t* _data[];
  size_t _xmit(const char str[]);
  size_t _xmit(char c);
  size_t _xmit(uint16_t n);
  size_t _xmit(unsigned long n, int base);
  size_t _xmit(unsigned long n, int base) ;
  size_t _xmitln(void) ;
  size_t _xmitln(const char c[]) ;
  size_t _xmitln(char c) ;


	
#endif
