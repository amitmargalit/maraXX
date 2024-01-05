//scale using Loacell an HX711 amp
#include "HX711.h"
HX711 scale;

#define LOADCELL_CALIBRATION_FACTOR 1755.00 // todo: set

void setupScale() {
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(LOADCELL_CALIBRATION_FACTOR); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  //scale.set_scale(); //sending empty for calibration
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  pinMode(TARE_PIN, INPUT);
}

void loopScale(){
  //scaleCount = scale.get_units(10); // for calibration
  //return;
  currentMillisScale = millis();
  if (currentMillisScale - previousMillisScale >= scaleInterval ) { // interval has passed since last reading
    previousMillisScale = currentMillisScale;
    scaleCount = round(scale.get_units(5) * 10) / 10.0;
    if (abs(scaleCount - prevScaleCount) >= scaleTolerance) { // siginficant enough change
      prevScaleCount = scaleCount;
    }
  }
  if (digitalRead(TARE_PIN)) {
    scale.tare();
    readyToBrew = true;
  }
}