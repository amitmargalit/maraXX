#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 128 // OLED display height, in pixels
#define OLED_RESET -1     // can set an oled reset pin if desired

#include <Adafruit_SH110X.h>
#include <Adafruit_GFX.h>
#include <Wire.h> // todo: I need this?

// Constructor
Adafruit_SH1107 display = Adafruit_SH1107(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 1000000, 100000);

void setupDisplay() {
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(250); // wait for the OLED to power up

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  //display.begin(0x3D, true); // Address 0x3D default
  display.begin(0x3C, true); // Address 0x3D default
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.display();
}


void loopDisplay() {
  ypos = 0;
  xpos = 0;
  display.clearDisplay();
  if (machineIsOn) {
      renderDashboard();
      //renderTest();
    }
  else {
    // Display the text "Machine off"
    centerText("MACHINE", 3, 30);
    centerText("OFF", 3, 70);
  }
  display.display();
}

void renderDashboard() {
    if (digitalRead(TARE_PIN)) {
    centerText("TARE", 3, SCREEN_HEIGHT/2);
  }
  else { // not taring RN
    // draw machine state C/S
    xpos += 1;
    ypos += 1;
    display.setTextSize(1);
    display.setCursor(xpos, ypos);
    if (maraMode == 'C') display.print("Coffee Mode");
    else if (maraMode == 'S') display.print("Steam Mode");
    

    if (heating) {
      xpos += 60;
      display.setCursor(xpos, ypos); // todo: I think I don't need to move cursor bc of mode print 
      display.print("Heating");
    }
    // down line
    xpos = 1;
    ypos += 9;
    display.setCursor(xpos, ypos);
    display.setTextSize(1);
    display.print("HX:");
    display.setTextSize(2);
    display.print(String(hxTempActual));
    display.setTextSize(1);
    display.print((char)247);
    display.print("C");
    if (heatingBoost) {
      display.print("       Boost");
    }
    // down line
    ypos += 18;
    display.setCursor(xpos, ypos);
    display.setTextSize(1);
    display.print("Br:");
    display.setTextSize(2);
    display.print(String(steamTempActual) + "/" + String(steamTempTarget));
    display.setTextSize(1);
    display.print((char)247);
    display.print("C");
    // down line
    ypos += 18;
    // draw line
    display.drawLine(0, ypos, SCREEN_WIDTH, ypos, SH110X_WHITE);
    // down line
    ypos += 2;
    display.setCursor(xpos, ypos);
    display.setTextSize(1);
    display.print("Scale:");
    // down line
    ypos += 9;
    display.setCursor(xpos, ypos);
    display.setTextSize(2);
    display.print(String(prevScaleCount, 1));
    display.print(" g");
    if (!timerStarted) {
      // down line
      ypos += 18;
      display.setCursor(xpos, ypos);
      display.setTextSize(1);
      display.print("Time:");
      // down line
      ypos += 9;
      display.setCursor(xpos, ypos);
      display.setTextSize(2);
      display.print(String(timerCount));
      display.print(" sec");
      ypos += 18;
      display.setCursor(xpos, ypos);
      display.setTextSize(1);
      display.print("Last shot:");
      ypos += 9;
      display.setCursor(xpos, ypos);
      display.print(String(lastShotWeight, 1) + " grams in "+ String(lastShotTime) + "sec");
    }
  display.display();
  }
}

void centerText(String text, uint8_t textSize, uint8_t yPosition) {
  // Calculate the X-coordinate to center the text
  uint8_t textWidth = text.length() * (textSize * 6); // Assuming 6 pixels per character
  uint8_t xPosition = (SCREEN_WIDTH - textWidth) / 2;
    // Set up the display
  display.setTextSize(textSize);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(xPosition, yPosition);
  // Print the centered text
  display.print(text);
}