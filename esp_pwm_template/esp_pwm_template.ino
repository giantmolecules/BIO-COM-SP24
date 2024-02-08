//----------------------------------------------------------------//
//
// SAIC Robotics Fall 2023
// Brett Ian Balogh
// https://github.com/giantmolecules/ROBOTICS_FA23_CODE.git
//
// esp_pwm_template.ino
//
// Starter code for PWM projects
//
//----------------------------------------------------------------//

// Set paramaters for PWM peripheral
const int freq = 5000;
const int resolution = 10;

void setup() {
  // Configure PWM: channel, frequency, resolution
  ledcSetup(0, freq, resolution);
  // Attach pin, channel
  ledcAttachPin(5, 0);
}

void loop() {
  //write channel, value
  ledcWrite(0, 0);
}
