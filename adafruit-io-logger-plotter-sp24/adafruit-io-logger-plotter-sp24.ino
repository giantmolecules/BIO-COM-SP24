//----------------------------------------------------------------//
//
// SAIC Biological Communications SP24
// Brett Ian Balogh
//
// https://github.com/giantmolecules/BIO-COM-SP24.git//
// 
// adafruit-io-logger-plotter-sp24.ino.ino
//
// Simultaneously plots to TFT and logs to Adafruit IO.
// Change SSID to your wifi network name.
// Change PASSWORD to your network password.
// Change USERNAME to your adafruit io username.
// Change KEY to your adafruit io key.
// Change path in line 50 to set your feed name like "/feeds/MY_FEED_NAME"
//
//----------------------------------------------------------------//

//----{INCLUDES}------------------------------------------------------//
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Wire.h>
#include <esp_task_wdt.h>
#include <time.h>

//----{DEFINES}------------------------------------------------------//

#define WLAN_SSID "SSID"
#define WLAN_PASS "PASSWORD"
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883  // use 8883 for SSL
#define AIO_USERNAME "USERNAME"
#define AIO_KEY "KEY"

#define WDT_TIMEOUT 15

// Define # of samples in filter buffer
#define BUFLEN 100
#define MAX_VALUE 8192

//----{INSTANCES}------------------------------------------------------//

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish physarum = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/physarum2");

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

//----{VARIABLES}------------------------------------------------------//

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -21600;
const int daylightOffset_sec = 3600;



int time_now = 0;
int time_then = 0;
int pubInterval = 3000;
bool pubNow = 0;

int physarumFilterBuffer[BUFLEN];

int phyReading = 0;
int avgPhysarumReading = 0;

int screenBuffer[240];

int counter = 0;

int lastTime = 0;
int lastTime2 = 0;
int lastTime3 = 0;

int displayInterval = 5;
int screenInterval = 5;
int printInterval = 100;
int largestValue = 0;
int smallestValue = 0;

//----{SETUP}------------------------------------------------------//

void setup() {

  // Set up serial comms
  Serial.begin(115200);

  // Setup TFT
  // turn on backlite
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
  // turn on the TFT / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // initialize TFT
  tft.init(135, 240);  // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  Serial.println(F("Initialized"));
  // Set text size
  tft.setTextSize(2);

  // Set text color
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  // Fill screen with a color. Can use hex rgb values
  tft.fillScreen(ST77XX_BLACK);

  // Setup WDT
  tft.println("Configuring WDT...");
  esp_task_wdt_init(WDT_TIMEOUT, true);  //enable panic so ESP32 restarts
  esp_task_wdt_add(NULL);                //add current thread to WDT watch

  // Setup WiFi
  tft.print("Connecting to ");
  tft.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  tft.print("Connecting to network");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tft.print(".");
  }
  tft.println("WiFi connected");
  tft.println("IP address: ");
  tft.println(WiFi.localIP());
  delay(3000);
  tft.fillScreen(ST77XX_BLACK);
  // Initialize Filter Buffers
  for (int i = 0; i < BUFLEN; i++) {
    physarumFilterBuffer[i] = analogRead(18);
    //physarumFilterBuffer[i] = 0;
    delay(10);
  }

  // initialize screen buffer
  for (int i = 0; i < 240; i++) {
    screenBuffer[i] = 0;
  }

  //Config Time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

//----{LOOP}------------------------------------------------------//

void loop() {

  // Pet the dog
  esp_task_wdt_reset();

  // Take sensor readings
  phyReading = analogRead(18);

  // Filter sensor readings
  avgPhysarumReading = updatePhysarumFilterBuffer(phyReading);

  // Kep MQTT Live
  MQTT_connect();

  // Publish everything
  time_now = millis();
  if (time_now - time_then > pubInterval || pubNow == 1) {
    statsPublish();
    updateScreenBuffer(avgPhysarumReading);
    updateDisplay();
    time_then = millis();
    pubNow = 0;
  }
}

//----{FUNCTIONS}------------------------------------------------------//

int updatePhysarumFilterBuffer(int val) {

  // shift values in the buffer
  for (int i = 0; i < BUFLEN - 1; i++) {
    physarumFilterBuffer[i] = physarumFilterBuffer[i + 1];
    //read the analog value from pin 18 (A0)
  }
  physarumFilterBuffer[BUFLEN - 1] = val;
  int sum = 0;

  for (int i = 0; i < BUFLEN; i++) {
    largestValue = 0;
    smallestValue = 0;
    if (physarumFilterBuffer[i] > largestValue) {
      largestValue = physarumFilterBuffer[i];
    }
    if(physarumFilterBuffer[i] < smallestValue){
      smallestValue = physarumFilterBuffer[i];
    }
    sum += physarumFilterBuffer[i];
  }

  int filteredValue = sum / BUFLEN;
  //constrain(filteredValue, 300, 1100);
  return filteredValue;
}



//----{}------------------------------------------------------//

void updateTFT() {

  tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);

  tft.setCursor(140, 0);
  tft.print(String(avgPhysarumReading));
  tft.println(" ");
}

//----{}------------------------------------------------------//

void statsPublish() {
  Serial.println();
  Serial.println("----{TIME}----------------");
  Serial.println();
  printLocalTime();
  Serial.println();

  Serial.println();
  Serial.println("----{READINGS}----------------");
  Serial.println();
  // Pub physarum State
  physarumPublish();
  Serial.println();
}

//----{}------------------------------------------------------//

void physarumPublish() {

  if (!physarum.publish(avgPhysarumReading)) {
    Serial.println(F("Physarum Failed"));
  } else {
    Serial.print(F("Physarum: "));
    Serial.println(avgPhysarumReading);
  }
}

//----{}------------------------------------------------------//

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT...");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {  // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      ESP.restart();
      //while (1);
    }
  }
  Serial.println("MQTT Connected!");
}

//----{}------------------------------------------------------//

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

//----{}------------------------------------------------------//

void updateDisplay() {

  tft.fillScreen(ST77XX_BLACK);
  //tft.fillRect(0, 18, 240, 134, ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  for (int i = 0; i < 239; i++) {
    //tft.drawPixel(i, screenBuffer[i], ST77XX_WHITE);
    tft.drawLine(i, screenBuffer[i], i + 1, screenBuffer[i + 1], ST77XX_WHITE);
  }
  tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.print(avgPhysarumReading);
}

//----{}------------------------------------------------------//

void updateScreenBuffer(int val) {

  for (int i = 0; i < 239; i++) {
    screenBuffer[i] = screenBuffer[i + 1];
    //tft.drawPixel(i, screenBuffer[i], ST77XX_WHITE);
  }

  int mappedValue = map(val, 0, MAX_VALUE, 134, 1);
  //int mappedValue = map(val, smallestValue, largestValue, 134, 1);

  screenBuffer[239] = mappedValue;
}


//----{EOF}------------------------------------------------------//
