#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

// Config
const char* SSID = "Margalit";
const char* PSK = "nivrik6xennuTehzin";
const char* MQTT_BROKER = "hb-margalit";
const char* MQTT_USER = "amit";
const char* MQTT_PASSWORD = "isbdvisd846dg";

char lastMachineIsOn;
int lastHxTempActual = 1;
int lastSteamTempActual = 1;
long lastTimerStartMillis = 0;
bool lastTimerStarted = false;
bool lastHeating;
bool lastHeatingBoost = false;

int lastLastShotTime;
int lastLastShotWeight;

unsigned long previousMillis = 0; // Variable to store the last time toggeled
const long MQTTinterval = 1000; // Interval in milliseconds (1 second)

void setupWifi() { 
  if (SSID != "" && PSK != "" && MQTT_BROKER != "") { // if you have wifi details
    WiFi.begin(SSID, PSK);
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
    }
    client.setServer(MQTT_BROKER, 1883);
    //client.setCallback(callback); // todo: set up callback for scale tare
  } else {
    WiFi.mode(WIFI_OFF);
  }
}

void updateWifi() {
  if (!client.connected()) {
    while (!client.connected()) {
      if ( MQTT_USER != "" && MQTT_PASSWORD != "" ) {
        client.connect("marax", MQTT_USER, MQTT_PASSWORD);
        delay(100);
        }
      else {
        client.connect("marax");
        delay(100);
      }
    }
  }
  
  client.loop();

  if (lastMachineIsOn != machineIsOn) {
    lastMachineIsOn = machineIsOn;
    broadcastMachineState();   
  }

  if (lastHxTempActual != hxTempActual) {
    lastHxTempActual = hxTempActual;
    if (hxTempActual > 15 && hxTempActual < 115 && abs(hxTempActual - lastHxTempActual) < 3) {
    broadcastHxTemperature();}
  }

  if (lastSteamTempActual != steamTempActual) {
    lastSteamTempActual = steamTempActual;
    if (steamTempActual > 15 && steamTempActual < 250 && abs(steamTempActual - lastSteamTempActual) < 3) {
    broadcastSteamTemperature();}
  }

  if (lastShotTime != lastLastShotTime){
    lastLastShotTime = lastShotTime;
    broadcastShot();
  }

  if (lastShotWeight != lastLastShotWeight){
    lastLastShotWeight = lastShotWeight;
    broadcastScale();
  }

  if (lastTimerStarted != timerStarted) {
    lastTimerStarted = timerStarted;
    broadcastPump();
  }
  
  if (lastHeating != heating) {
    lastHeating = heating;
    broadcastMachineHeating();
  }

  if (lastHeatingBoost != heatingBoost) {
    lastHeatingBoost = heatingBoost;
    broadcastMachineHeatingBoost();
  }
  unsigned long currentMillis = millis(); // Get the current time //todo: use this
  // Check if one second has passed
  if (currentMillis - previousMillis >= MQTTinterval) {
    // Save the current time
    previousMillis = currentMillis;
    //broadcastScale();
  }
  //client.subscribe("/marax/tare");
}


void broadcastMachineState() {
  if (!machineIsOn) {
    client.publish("/marax/power", "off");
  } else {
    client.publish("/marax/power", "on");
  }
}

void broadcastHxTemperature() {
  client.publish("/marax/hx", String(hxTempActual).c_str());
}

void broadcastSteamTemperature() {
  client.publish("/marax/steam", String(steamTempActual).c_str());
}

void broadcastShot() {
  client.publish("/marax/shot", String(lastShotTime).c_str());
}

void broadcastScale() {
  client.publish("/marax/scale", String(lastShotWeight).c_str());
}

void broadcastPump() {
  if (timerStarted) {
    client.publish("/marax/pump", "on");
  } else {
    client.publish("/marax/pump", "off");
  }
}

void broadcastMachineHeating () {
  if (heating) {
    client.publish("/marax/machineheating", "on");
  } else {
    client.publish("/marax/machineheating", "off");
  }
}

void broadcastMachineHeatingBoost () {
  if (heatingBoost) {
    client.publish("/marax/machineheatingboost", "on");
  } else {
    client.publish("/marax/machineheatingboost", "off");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Message arrived on topic: " + String(topic));

  // Convert the payload to a string
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println("Payload: " + message);
  // Check the message and call your function
  if (message == "1" || message == "true" || message.equalsIgnoreCase("on")) {
    scale.tare();  // Replace with your actual function call
  }
}