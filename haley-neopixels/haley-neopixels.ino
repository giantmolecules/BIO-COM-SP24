#include "FS.h"
#include "SPIFFS.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define LED_COUNT 16

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int minValue = 8192;
int maxValue = 0;
int buffer[LED_COUNT];
int numLines = 0;
File file;

void setup() {
  Serial.begin(9600);
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  // Open file for reading
  file = SPIFFS.open("/values.txt", "r");
  if (!file) {
    Serial.println("Failed to open file for reading 1");
    return;
  }

  Serial.println("File Content:");
  numLines = 0;
  // Read file line by line
  while (file.available()) {
    String line = file.readStringUntil('\n');
    
    //Serial.println(line);
    int currentValue = line.toInt();
    if (currentValue < minValue) {
      minValue = currentValue;
    }
    if (currentValue > maxValue) {
      maxValue = currentValue;
    }
    numLines++;
  }

  Serial.print(" Number of Lines: ");
  Serial.print(numLines);
  Serial.print(" Min Value: ");
  Serial.print(minValue);
  Serial.print(" Max Value: ");
  Serial.println(maxValue);
  //file.close();  // Close the file

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  for(int i = 0; i < LED_COUNT; i++){
    strip.setPixelColor(i, 255,255,255,0);
  }
  strip.show();            // Turn OFF all pixels ASAP
  //strip.setBrightness(0);  // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {

  // Open file for reading
  // File file = SPIFFS.open("/values.txt", "r");
  // if (!file) {
  //   Serial.println("Failed to open file for reading 2");
  //   return;
  // }

  // Serial.println("File Content:");

  // Read file line by line
  file.seek(0, fs::SeekSet);
  numLines = 0;
  while (file.available()) {
    String line = file.readStringUntil('\n');
    //Serial.println(line);
    int currentValue = line.toInt();
    currentValue = map(currentValue, minValue, maxValue,0,255);
    currentValue = constrain(currentValue, 0, 255);
    //Serial.println(currentValue);
    for(int i = LED_COUNT-1; i > 0; i--){
        buffer[i] = buffer[i-1];
    }
    buffer[0] = currentValue;
    Serial.print("# ");
    Serial.print(numLines);
    Serial.print("  ");
    for(int i = 0; i < LED_COUNT; i++){
        strip.setPixelColor(i, 155-buffer[i],155-buffer[i],0);
        Serial.print(buffer[i]);
        Serial.print(", ");
    }
    strip.show();
    Serial.println();
    delay(10);
    numLines++;
  }

  //file.close();  // Close the file
}
