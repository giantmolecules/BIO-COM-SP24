//----------------------------------------------------------------//
//
// SAIC Robotics Fall 2023
// Brett Ian Balogh
// https://github.com/giantmolecules/ROBOTICS_FA23_CODE.git
//
// project_template.ino
//
// Q: Which pins can you attach to PWM peripheral? 
// A: All but 35, 36, 37, 41, 42
//----------------------------------------------------------------//

// Include libraries for TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

int pins[] = {1, 2, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 35, 36, 37, 41, 42};

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
  tft.setTextSize(3);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  Serial.println(F("TFT Initialized"));

  // Configure PWM
  ledcSetup(ledChannel, freq, resolution);
  // Attach pins to PWM preipheral
  for (int i = 0; i < 20; i++) {
    //pinMode(i, OUTPUT);
    ledcAttachPin(i, ledChannel);
  }

}

//----{LOOP}------------------------------------------------------//

void loop() {
  
  for (int j = 0; j < 256; j++) {
    for (int i = 0; i < 20; i++) {
      //analogWrite(i, j);
      ledcWrite(i, j);
    }
    delay(10);
  }
  
  for (int j = 255; j > 0; j--) {
    for (int i = 0; i < 20; i++) {
      //analogWrite(i, j);
      ledcWrite(i, j);
    }
    delay(10);
  }
  
}

//----{END}------------------------------------------------------//
