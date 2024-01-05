//reWriting this project from scratch
//using #include "HX711.h" instead of #include <HX711_ADC.h>
#include <SoftwareSerial.h>
#include "myheader.h"
#include <ArduinoOTA.h>


void setup() {
  //Serial.begin(9600);
  setupDisplay();
  setupMaraXSerial();
  setupTimer();
  setupScale();
  setupWifi();
  setupOTA();
}

void loop() {
  // put your main code here, to run repeatedly:
  loopTimer();
  loopScale(); //todo: get object reading from this
  loopSerial();
  loopDisplay();
  ArduinoOTA.handle();
}
