// Constructor
SoftwareSerial maraXSerial(MARAX_TX, MARAX_RX);

void setupMaraXSerial() {
  //maraXSerial.begin(9600, SERIAL_8N1, MARAX_RX, MARAX_TX); //9600 baud
  maraXSerial.begin(9600); //9600 baud
  //pinMode(LED_BUILTIN, OUTPUT); // todo: I need this?
}

void loopSerial() {
  // read serial info every time interval
  currentMillisSerial = millis();
  if (currentMillisSerial - previousMillisSerial >= serialInterval) {
    previousMillisSerial = currentMillisSerial;
    readSerial();
    // separate data from read serial string
    if (maraXSerial.available() > 0) {
      maraMode = maraxstatus[0];
      steamTempActual = atoi( &maraxstatus[6] );
      steamTempTarget = atoi( &maraxstatus[10] );
      hxTempActual = atoi( &maraxstatus[14] );
      boostTime = atoi( &maraxstatus[18] );
      heatingBoost = (boostTime != 0);
      heating = (atoi( &maraxstatus[23] ) != 0);
    } else {
        // Serial data not available, handle accordingly
        machineIsOn = false;
    }
  }
}

void readSerial(){
  // read the serial buffer
  while (maraXSerial.available()) {
    machineIsOn = true;
    ch = maraXSerial.read();
    if ( (ch == 'C') || (ch == 'V')) {
      serialCharIndex = 0;
    }
    if (serialCharIndex < LEN) {
      maraxstatus[serialCharIndex] = ch;
      //serialCharIndex = serialCharIndex + 1;
      serialCharIndex += 1;
    }
    if (serialCharIndex >= LEN) {
      serialCharIndex = 0;
      break;
    }
  }
}