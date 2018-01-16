#include <SoftwareSerial.h>
SoftwareSerial softSerial(9, 10); // RX, TX. Connect TX to Display's RO.

#include <WeatherBugDisplay.h>
WeatherBugDisplay disp = WeatherBugDisplay(&softSerial);

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial) ;
  Serial.println();

}

void loop() {

  Serial.println("sending");
  disp.setTime();
  
  digitalWrite(LED_BUILTIN, HIGH); //mimics MCU LED, but doesn't pulse RS485
  disp.update();
  digitalWrite(LED_BUILTIN, LOW);

  delay(100); //This can possibly be lower, but cannot be zero

}
