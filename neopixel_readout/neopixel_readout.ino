//----------------------------------------------------------------//
//
// SAIC Robotics Fall 2023
// Brett Ian Balogh
// https://github.com/giantmolecules/ROBOTICS_FA23_CODE.git
//
// neopixel_readout.ino
//
// This is an example of using the on-board neopixel and printing
// the RGB values to the TFT. 
//
//----------------------------------------------------------------//

#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Which pin on the ESP32 is connected to the NeoPixels?
#define PIN        33 // 

// There's only one neopixel on the SP32
#define NUMPIXELS 1 // 

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 20 // Time (in milliseconds) to pause between pixels

//----{SETUP}-----------------------------------------------------//

void setup() {

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
  tft.setTextSize(2);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
}

//----{LOOP}------------------------------------------------------//

void loop() {

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.

  // Count up
  for (int c = 0; c < 256; c++) {
    for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixels.setPixelColor(i, pixels.Color(255 - c, 0, c));

    }
    pixels.show();   // Send the updated pixel colors to the hardware.
    
    tft.setCursor(0,0);
    tft.print("R: ");
    tft.print(255 - c);
    tft.print(" G: ");
    tft.print(0);
    tft.print(" B: ");
    tft.print(c);
    tft.print(" ");
    
    delay(DELAYVAL); // Pause before next pass through loop
  }

  // Count down
  for (int c = 255; c > 0; c--) {
    for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixels.setPixelColor(i, pixels.Color(255 - c, 0, c));

    }
    pixels.show();   // Send the updated pixel colors to the hardware.

    tft.setCursor(0,0);
    tft.print("R: ");
    tft.print(255 - c);
    tft.print(" G: ");
    tft.print(0);
    tft.print(" B: ");
    tft.print(c);
    tft.print(" ");

    delay(DELAYVAL); // Pause before next pass through loop
  }

}

//----{END}------------------------------------------------------//
