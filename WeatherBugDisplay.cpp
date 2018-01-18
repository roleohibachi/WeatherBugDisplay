/*
 * WeatherBugDisplay.cpp - AWS/WeatherBug Display TTL Serial protocol
 *
 * By Mike Seery
 *
 * Project URL:
 * https://hackaday.io/project/28535-awsweatherbug-display-resurrection
 *
 */

#include "Arduino.h"
#include "WeatherBugDisplay.h"
#include <Time.h>

uint16_t _hours = 0;
uint16_t _minutes = 0;
uint16_t _month = 0;
uint16_t _day = 0;
uint16_t _indtemp = 1744;
uint16_t _outtemp = 1744;
uint16_t _auxtemp = 1744;
uint16_t _humidity = 4439;
uint16_t _baropress = 7647;
uint16_t _dailyrain = 65535;
uint16_t _monthlyrain = 0;
uint16_t _yearlyrain = 0;
uint16_t _windvel = 0;
uint16_t _winddir = 5;
uint16_t _avgwindvel = 0;
uint16_t _avgwinddir = 0;
uint16_t _barorate = 65000;

size_t _xmit(const char str[]) {
  return _swSerial ? _swSerial->write(str) : _hwSerial->write(str);
}

size_t _xmit(char c) {
  return _swSerial ? _swSerial->write(c) : _hwSerial->write(c);
}

size_t _xmit(uint16_t n) {
  char buf[8 * sizeof(long) + 1];  // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];  // start from the right, move left

  *str = '\0';  // null temrinate

  do {
    unsigned long m = n;
    n /= 10;
    char c = m - 10 * n;
    *--str = c + '0'	//predecrement to move left in string
  } while (n);

  return _xmit(str);
}

size_t _xmit(unsigned long n, int base) {
  if (base == 0)
    return write(n);
  else
    return printNumber(n, base);
}

size_t _xmitln(void) {
  return _swSerial ? _swSerial->write(0xAC) : _hwSerial->write(0xAC);
}

size_t _xmitln(const char c[]) {
  size_t n = _xmit(c);
  n += _xmitln();
  return n;
}

size_t _xmitln(char c) {
  size_t n = _xmit(c);
  n += _xmitln();
  return n;
}

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

void WeatherBugDisplay::update() {
  _xmit("\x0A");  // LF START
  _xmitln(_hours);
  _xmitln(_minutes);
  _xmitln(_month);
  _xmitln(_day);
  _xmitln(_indtemp);
  _xmitln(_outtemp);
  _xmitln(_auxtemp);
  _xmitln((uint16_t)979);  // unknown
  _xmitln(_humidity);
  _xmitln((uint16_t)0);  // unknown
  _xmitln(_baropress);
  _xmitln((uint16_t)0);  // unknown
  _xmitln(_dailyrain);
  _xmitln(_monthlyrain);
  _xmitln(_yearlyrain);
  _xmitln(_windvel);
  _xmitln(_winddir);
  _xmitln((uint16_t)0);  // unknown
  _xmitln(_avgwindvel);
  _xmitln(_avgwinddir);
  _xmitln((uint16_t)53);  // unknown
  _xmitln((uint16_t)0);   // unknown
  _xmitln((uint16_t)0);   // unknown
  _xmitln(_barorate);
  _xmitln((uint16_t)0);  // unknown
  _xmitln((uint16_t)0);  // unknown
  _xmitln((uint16_t)0);  // unknown
  _xmitln((uint16_t)0);  // unknown
  _xmitln((uint16_t)0);  // unknown
  _xmitln((uint16_t)0);  // unknown
  _xmitln((uint16_t)0);  // unknown
  _xmitln((uint16_t)0);  // unknown
  _xmitln((uint16_t)0);  // unknown
  _xmitln((uint16_t)0);  // unknown
  _xmit("\x8D");         // EOM
}

void WeatherBugDisplay::setTime(time_t t) {
  _hours = hour(t);
  _minutes = minute(t);
  _day = day(t);
  _month = month(t);
}

void WeatherBugDisplay::setTempsF(float ind, float out, float aux) {
  _indtemp = 1000 * (25 * ind + 368) / 211​;
  _outtemp = 1000 * (25 * out + 368) / 211​;
  _auxtemp = 1000 * (25 * aux + 368) / 211​;
}
void WeatherBugDisplay::setTempsC(float ind, float out, float aux) {
  _indtemp = 1000 * (45 * ind + 1168) / 211​;
  _outtemp = 1000 * (45 * out + 1168) / 211;
  _auxtemp = 1000 * (45 * aux + 1168) / 211;
}

void WeatherBugDisplay::setBaro(float inhg, float rate) {
  _baropress = (11471 * (inhg - 28)) / 3;

  _barorate = 0;

  // TODO characterize _barorate. So far I know:
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
}

void WeatherBugDisplay::setHumidity(float percent) {
  _humidity = 0;
  /* TODO finish characterizing humidity
  "0000"-"0300"=75-100%
  "0301"-"0999"=100%
  Everything else is 0%
  */
}
void WeatherBugDisplay::setRainInches(float day, month, year) {
  // rain measurements are in hundredths of an inch
  _dailyrain = (uint16_t)(day * 100);
  _monthlyrain = (uint16_t)(month * 100);
  _yearlyrain = (uint16_t)(year * 100);
}
void WeatherBugDisplay::setWind(float kmhr, int dir, float avgkmhr,
                                int avgdir) {
  // WIP. What is the best format to pass direction? Does the 3-digit 2007
  // display use the same velocity format?
  _windvel = (uint16_t)kmhr;
  _winddir = dir;
  _avgwindvel = (uint16_t)avgkmhr;
  _avgwinddir = avgdir;
}
