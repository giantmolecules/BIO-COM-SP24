//----------------------------------------------------------------//
//
// SAIC Robotics Fall 2023
// Brett Ian Balogh
// https://github.com/giantmolecules/ROBOTICS_FA23_CODE.git
//
// potentiometer_fade_led.ino
//
// Fade an led by turning a potentiometer.
//
//----------------------------------------------------------------//

// Include libraries for TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8; // 8 -> 255

//----{SETUP}-----------------------------------------------------//

void setup() {

  // Start Serial COM for debugging
  Serial.begin(115200);

  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // initialize TFT
  tft.init(135, 240); // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  // default text size
  tft.setTextSize(5);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  Serial.println(F("TFT Initialized"));

  pinMode(5, INPUT);

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(6, ledChannel);
}

//----{LOOP}------------------------------------------------------//

void loop() {

  int analogValue = analogRead(5);
  
  tft.setCursor(0,0);
  tft.println(analogValue);

  int scaledValue = map(analogValue, 0, 4095, 0, 255); // map larger range on smaller one

  ledcWrite(ledChannel, scaledValue); // write value to channel

  tft.println(scaledValue);
}

//----{END}------------------------------------------------------//
