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
int capIn1 = 9;  // GPIO pin used to connect the potentiometer (analog in)
int capIn2 = 10;
int ADC_Max = 4096;  // This is the default ADC max value on the ESP32 (12 bit ADC width);
// this width can be set (in low-level oode) from 9-12 bits, for a
// a range of max values of 512-4096

int val1;  // variable to read the value from the analog pin
int val2;
int midpoint = 90;
int minAngle = 20;
int maxAngle = 160;
int oldVal1 = 0;
int oldVal2 = 0;
int dist1 = 0;
int dist2 = 0;
int step1 = 0;
int step2 = 0;
int numSteps = 20;
int interpVal1 = 0;
int interpVal2 = 0;
int maxCapVal = 34000;
bool moving1 = 0;
bool moving2 = 0;
int capThresh = 33000;
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
  tft.setTextSize(4);

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
  myservo1.write(midpoint);
  myservo2.setPeriodHertz(50);            // Standard 50hz servo
  myservo2.attach(servoPin2, 500, 2400);  // attaches the servo on pin 18 to the servo object
  myservo2.write(midpoint);
  // using SG90 servo min/max of 500us and 2400us
  // for MG995 large servo, use 1000us and 2000us,
  // which are the defaults, so this line could be
  // "myservo.attach(servoPin);"
}

//----{LOOP}------------------------------------------------------//

void loop() {
  if (touchRead(capIn1) > capThresh) {
    if (moving1 == false) {
      val1 = touchRead(capIn1);
      Serial.print("Cap1: ");
      Serial.println(val1);
      val1 = constrain(val1, 0, maxCapVal);
      val1 = map(val1, 0, maxCapVal, minAngle, maxAngle);
      val1 = constrain(val1, minAngle, maxAngle);
      val1 = int(random(val1));
      moving1 = true;
    }
  }
if(touchRead(capIn2) > capThresh){
  if (!moving2) {
    val2 = touchRead(capIn2);
    Serial.print(" Cap2: ");
    Serial.println(val2);
    val2 = constrain(val2, 0, maxCapVal);
    val2 = map(val2, 0, maxCapVal, minAngle, maxAngle);
    val2 = constrain(val2, minAngle, maxAngle);
    val2 = int(random(val2));
    moving2 = true;
  }
}

  //Serial.println("");

  if (val1 > oldVal1 && moving1) {
    oldVal1++;
    if (oldVal1 >= val1) {
      oldVal1 = val1;
      moving1 = false;
    } else {
      myservo1.write(oldVal1);
    }
  }

  if (val1 < oldVal1 && moving1) {
    oldVal1--;
    if (oldVal1 <= val1) {
      oldVal1 = val1;
      moving1 = false;
    } else {
      myservo1.write(oldVal1);
    }
  }

  if (oldVal1 == val1) {
    moving1 = false;
  }

  if (val2 > oldVal2 && moving2) {
    oldVal2++;
    if (oldVal2 >= val2) {
      oldVal2 = val2;
      moving2 = false;
    } else {
      myservo2.write(oldVal2);
    }
  }

  if (val2 < oldVal2 && moving2) {
    oldVal2--;
    if (oldVal2 <= val2) {
      oldVal2 = val2;
      moving2 = false;
    } else {
      myservo2.write(oldVal2);
    }
  }

  if (oldVal2 == val2) {
    moving2 = false;
  }

  // Serial.print("Val1: ");
  // Serial.print(val1);
  // Serial.print("  oldVal1: ");
  // Serial.print(oldVal1);
  // Serial.print(" Moving: ");
  // Serial.print(moving1);
  // Serial.println("");

  delay(10);
  /*
  Serial.print("Cap1: ");
  Serial.print(val1);
  Serial.print(" Cap2: ");
  Serial.println(val2);
  Serial.print("  ");

 

  val1 = map(val1, 0, maxCapVal, minAngle, maxAngle);
  val1 = constrain(val1, minAngle, maxAngle);
  //int randomVal1 = int(random(-val1, val1));
  int randomVal1 = int(random(minAngle, maxAngle));

  val2 = map(val2, 0, maxCapVal, minAngle, maxAngle);
  val2 = constrain(val2, minAngle, maxAngle);
  //int randomVal2 = int(random(-val2, val2));
  int randomVal2 = int(random(minAngle, maxAngle));

  dist1 = randomVal1 - oldVal1;
  dist2 = randomVal2 - oldVal2;

  Serial.print("dist1: ");
  Serial.print(dist1);
  Serial.print(" dist2: ");
  Serial.print(dist2);
  Serial.print("  ");

  step1 = dist1 / numSteps;
  step2 = dist2 / numSteps;

  Serial.print("Step1: ");
  Serial.print(step1);
  Serial.print(" Step2: ");
  Serial.println(step2);
  Serial.print("  ");

  Serial.println("");
  interpVal1 = randomVal1;
  interpVal2 = randomVal2;

  for (int i = 0; i <= numSteps; i++) {

    interpVal1 += step1;
    interpVal1 = constrain(interpVal1, minAngle, maxAngle);
    myservo1.write(interpVal1);

    interpVal2 += step2;
    interpVal2 = constrain(interpVal2, minAngle, maxAngle);
    myservo2.write(interpVal2);

    tft.setCursor(0, 0);
    tft.print(interpVal1);
    tft.print(" ");
    tft.print(interpVal2);
    tft.println("   ");

    delay(100);
  }

  oldVal1 = interpVal1;
  oldVal2 = interpVal2;
  */
}

//----{END}------------------------------------------------------//
