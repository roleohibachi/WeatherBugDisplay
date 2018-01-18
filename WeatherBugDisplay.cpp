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

#define datalen 36

int _hours = 0;
int _minutes = 0;
int _month = 0;
int _day = 0;
int _indtemp = 1744;
int _outtemp = 1744;
int _auxtemp = 1744;
int _humidity = 4439;
int _baropress = 7647;
int _dailyrain = 65535;
int _monthlyrain = 0;
int _yearlyrain = 0;
int _windvel = 0;
int _winddir = 5;
int _avgwindvel = 0;
int _avgwinddir = 0;
int _barorate = 65000;

size_t _xmit(const char str[]) {
  return _swSerial ? _swSerial->write(str) : _hwSerial->write(str);
}

size_t _xmit(char c) {
  return _swSerial ? _swSerial->write(c) : _hwSerial->write(c);
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
  _xmit("\x0A");
  _xmitln(_hours);
  _xmitln(_minutes);
  _xmitln(_month);
  _xmitln(_day);
  _xmitln(_indtemp);
  _xmitln(_outtemp);
  _xmitln(_auxtemp);
  _xmitln(979);  // unknown
  _xmitln(_humidity);
  _xmitln(0);  // unknown
  _xmitln(_baropress);
  _xmitln(0);  // unknown
  _xmitln(_dailyrain);
  _xmitln(_monthlyrain);
  _xmitln(_yearlyrain);
  _xmitln(_windvel);
  _xmitln(_winddir);
  _xmitln(0);  // unknown
  _xmitln(_avgwindvel);
  _xmitln(_avgwinddir);
  _xmitln(53);  // unknown
  _xmitln(0);  // unknown
  _xmitln(0);  // unknown
  _xmitln(_barorate);
  _xmitln(0);  // unknown
  _xmitln(0);  // unknown
  _xmitln(0);  // unknown
  _xmitln(0);  // unknown
  _xmitln(0);  // unknown
  _xmitln(0);  // unknown
  _xmitln(0);  // unknown
  _xmitln(0);  // unknown
  _xmitln(0);  // unknown
  _xmitln(0);  // unknown
  _xmit("\x8D");  // EOM
}

void WeatherBugDisplay::setTime(time_t t) {
  _hours = hour(t);
  _minutes = minute(t);
  _day = day(t);
  _month = month(t);
}
