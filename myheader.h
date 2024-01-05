// myheader.h
#ifndef MYHEADER_H  // Header guards to prevent multiple inclusion
#define MYHEADER_H

// func declerations
void setupMaraXSerial();
void setupTimer();
void setupScale();
void setupWifi();
void setupOTA();

// consts
#define D8 (15) // for tare button - D8 is pulled to GND 
#define TARE_PIN D8
#define D5 (14) // MARAX_TX - goes to RX of MCU
#define D6 (12) // MARAX_RX - goes to TX of MCU
#define MARAX_RX D6
#define MARAX_TX D5
#define D7 (13) // for pump
#define PUMP_PIN D7
#define LEN 24 //chracter length of read string
#define D3 (0) // scale sck
#define D4 (2) // scale dt
#define LOADCELL_SCK_PIN D3
#define LOADCELL_DOUT_PIN D4
#define SCALE_INTERVAL 10000 //time to reset when nothing changes


// vars
// global vars
bool readyToBrew = true;
bool machineIsOn = true;
// Serial vars
char maraMode = 'X'; // C -offee or V -apour prio
bool heatingBoost;
bool heating;
int steamTempActual;
int steamTempTarget;
int hxTempActual;
int boostTime;
char maraxstatus[30];
char ch;
int serialCharIndex = 0;
unsigned long currentMillisSerial;
unsigned long previousMillisSerial = 0;
const int serialInterval = 1000; //time to update read serial
//timer vars
int timerCount = 0;
int lastShotTime = 0;
bool timerStarted = false;
long timerStartMillis = 0;
long timerStopMillis = 0;
// display vars
int ypos;
int xpos;
// scale vars
float scaleCount = 00.0;
float prevScaleCount = 00.0;
float scaleTolerance = 0.2;
float lastShotWeight = 00.0;
unsigned long currentMillisScale = 0;
unsigned long previousMillisScale = 0;
const int scaleInterval = 500; //time to update read scale

#endif

/* Good reads for the project
https://www.home-barista.com/espresso-machines/lelit-marax-data-visualisation-mod-t66187.html // serial
https://www.reddit.com/r/espresso/comments/17g2001/lelit_mara_x_v2_gicar_aux_port_pinout/ // voltage from gicar
https://github.com/zierroff/MQTT-MaraX // someone that opened the gicar
https://community.home-assistant.io/t/home-assistant-integration-for-lelit-marax-with-esphome/530847/3 // HA project
https://github.com/benovic/marax_display/blob/main/marax_display/marax_display.ino#L106 // similar project with external scale
https://github.com/alexrus/marax_timer/tree/main // OG project
https://github.com/alexander-heimbuch/marax_timer/blob/main/main/main.ino // OG project fork with MQTT
https://github.com/bogde/HX711/blob/master/examples/HX711_full_example/HX711_full_example.ino // my HX711 libraray
https://github.com/olkal/HX711_ADC/blob/master/examples/Read_1x_load_cell_interrupt_driven/Read_1x_load_cell_interrupt_driven.ino // another HX711 library I find less sexy
https://github.com/adafruit/Adafruit_SH110x/blob/master/examples/SH1107_128x128/SH1107_128x128.ino // SH1107 example
https://circuitjournal.com/50kg-load-cells-with-HX711 // a great load cell how-to (uses the least favourite HX711 librbay)
*/

