//----------------------------------------------------------------//
//
// SAIC Robotics Fall 2023
// Brett Ian Balogh
// https://github.com/giantmolecules/ROBOTICS_FA23_CODE.git
//
// servo_photocell.ino
//
// Connect photocell to pin 5 to control servo position.
//
//----------------------------------------------------------------//

// Include libraries for TFT
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
// Include the ESP32 Arduino Servo Library instead of the original Arduino Servo Library
#include <ESP32Servo.h>

// Create a TFT object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
Servo myservo1;  // create servo object to control a servo
Servo myservo2;

// Possible PWM GPIO pins on the ESP32: 0(used by on-board button),2,4,5(used by on-board LED),12-19,21-23,25-27,32-33
int servoPin1 = 12;  // GPIO pin used to connect the servo control (digital out)
int servoPin2 = 13;
// Possible ADC pins on the ESP32: 0,2,4,12-15,32-39; 34-39 are recommended for analog input
int capIn1 = 9;      // GPIO pin used to connect the potentiometer (analog in)
int capIn2 = 10;
int ADC_Max = 4096;  // This is the default ADC max value on the ESP32 (12 bit ADC width);
// this width can be set (in low-level oode) from 9-12 bits, for a
// a range of max values of 512-4096

int val1;  // variable to read the value from the analog pin
int val2;
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
  tft.init(135, 240);  // Init ST7789 240x135
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  // default text size
  tft.setTextSize(12);

  // set text foreground and background colors
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  Serial.println(F("TFT Initialized"));

  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo1.setPeriodHertz(50);            // Standard 50hz servo
  myservo1.attach(servoPin1, 500, 2400);  // attaches the servo on pin 18 to the servo object
  myservo2.setPeriodHertz(50);            // Standard 50hz servo
  myservo2.attach(servoPin2, 500, 2400);  // attaches the servo on pin 18 to the servo object
  // using SG90 servo min/max of 500us and 2400us
  // for MG995 large servo, use 1000us and 2000us,
  // which are the defaults, so this line could be
  // "myservo.attach(servoPin);"
}

//----{LOOP}------------------------------------------------------//

void loop() {
  val1 = touchRead(capIn1); 
  val2 = touchRead(capIn2);           
  val1 = map(val1, 0, 70000, 0, 180);
  val1 = constrain(val1, 0, 180);
   val2 = map(val2, 0, 70000, 0, 180);
   val2 = constrain(val2, 0, 180);
  myservo1.write(val1);
  myservo2.write(val2);
  tft.setCursor(0, 0);
  tft.print(val1);
  tft.print(" ");
  tft.print(val2);
  tft.println("   ");
}

//----{END}------------------------------------------------------//
