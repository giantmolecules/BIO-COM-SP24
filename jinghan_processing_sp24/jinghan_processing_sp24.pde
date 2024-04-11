import processing.serial.*;
import processing.pdf.*;

Serial myPort;              // The serial port
ArrayList<PVector> points;  // List to store points of the shape
int centerX, centerY;       // Center of the shape
float valueFromSerial = 50; // Distance from center, updated via serial
long startTime;             // Start time for drawing
boolean drawing = false;    // Flag to check if we should start drawing
int maxValue = 60000;
int minValue = 11000;
int offset = 50;

void setup() {
  size(600, 600);
  smooth();
  // List all the available serial ports
  printArray(Serial.list());
  // Open the first serial port
  myPort = new Serial(this, Serial.list()[2], 115200);
  // Don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  centerX = width / 2;
  centerY = height / 2;
  background(255);
  stroke(0);
  frameRate(30); // Adjust this for smoother or faster drawing
  points = new ArrayList<PVector>();
  beginRecord(PDF, "jinghan.pdf");
}

void draw() {
  background(255); // Clear the background each frame
  if (drawing) {
    beginShape();
    float elapsedTime = millis() - startTime;
    float duration = 3000; // Duration of 3 seconds to complete the shape
    if (elapsedTime < duration) {
      // Recalculate and redraw the shape with the current points
      drawShapeWithCurrentPoints();
    } else {
      drawing = false; // Stop drawing after 3 seconds
      // Ensure the shape is closed by connecting the last and first points
      //if (points.size() > 1) {
      //  PVector start = points.get(0);
      //  PVector end = points.get(points.size() - 1);
      //  line(start.x, start.y, end.x, end.y);
      //}
    }
  }
}

void drawShapeWithCurrentPoints() {
  for (int i = 0; i < points.size() - 1; i++) {
    PVector start = points.get(i);
    PVector end = points.get(i + 1);
    line(start.x, start.y, end.x, end.y);
  }
}

void serialEvent(Serial myPort) {
  // Get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    // Trim off any whitespace:
    inString = trim(inString);
    // Convert to a float and update the distance value from the center
    valueFromSerial = int(inString);
    println(valueFromSerial);
    valueFromSerial = map(valueFromSerial, minValue, maxValue, 0, height/2-offset);
    // Calculate new point based on the latest serial value
    float angle = TWO_PI * (points.size() / 360.0);
    float x = centerX + cos(angle) * valueFromSerial*offset;
    float y = centerY + sin(angle) * valueFromSerial*offset;
    /*
    print("X: ");
    print(x);
    print(" Y: ");
    println(y);
    */
    points.add(new PVector(x, y));
    
    if (!drawing) {
      // Reset the start time and start drawing
      startTime = millis();
      drawing = true;
    }
  }
}

void keyPressed() {
  if (key == 'q') {
    endRecord();
    exit();
  }
}
