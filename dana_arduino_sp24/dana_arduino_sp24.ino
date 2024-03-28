void setup() {
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);
}

void loop() {
  // Read the analog values from pins 17 and 18
  int analogValuePin17 = analogRead(17);
  int analogValuePin18 = analogRead(18);

  // Transmit the values over serial in comma-separated format, terminated with a newline
  Serial.print(analogValuePin17);
  Serial.print(",");
  Serial.print(analogValuePin18);
  Serial.println();

  // Small delay to stabilize readings and avoid flooding the serial output
  delay(100);
}
