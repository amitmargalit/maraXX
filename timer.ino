void setupTimer() {
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(PUMP_PIN, INPUT_PULLUP);
}

void loopTimer() {
  digitalWrite(LED_BUILTIN, digitalRead(PUMP_PIN));
  if (!timerStarted && !digitalRead(PUMP_PIN)) { // timer not known as started, pump on
    timerStartMillis = millis();
    timerStarted = true;
    Serial.println("Start pump");
  }
  if (timerStarted && digitalRead(PUMP_PIN)) { // timer already known as started, pump off
    if (timerStopMillis == 0) {
      timerStopMillis = millis();
    }
    if (millis() - timerStopMillis > 500) {
      if (timerCount > 15) { // pump off after brewing, set last shot
        lastShotTime = timerCount;
        lastShotWeight = scaleCount;
      }
      timerStarted = false;
      readyToBrew = false;
      timerStopMillis = 0;
      timerCount = 0;
//      display.invertDisplay(false);
      Serial.println("Stop pump");
    }
  } else {
    timerStopMillis = 0;
  }
  if (timerStarted) {
    timerCount = (millis() - timerStartMillis ) / 1000;
    if (timerCount == 0) {
      scale.tare();
    }
  }
}

int getTimer() { // not in use
  if (timerStarted) {
    timerCount = (millis() - timerStartMillis ) / 1000;
    if (timerCount > 15) {
      lastShotTime = timerCount;
    }
  } else {
    timerCount = lastShotTime;
  }
  return timerCount;
}