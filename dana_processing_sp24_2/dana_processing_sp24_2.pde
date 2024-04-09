import processing.serial.*;

Serial myPort;       // The serial port
String inputData = ""; // For storing the incoming serial data
float x, y;          // Variables to store the current position of the circle
float prevX, prevY;  // Variables to store the previous position of the circle

// Adjust these values to get best drawing coverage

int minValueX = 400;
int maxValueX = 4000;
int minValueY = 5000;
int maxValueY = 7000;


void setup() {
  size(500, 500);
  background(255);
  println(Serial.list()); // Print the list of available serial ports

  // Initialize the serial port - replace 0 with the correct index from Serial.list()
  myPort = new Serial(this, Serial.list()[2], 115200);
  myPort.bufferUntil('\n'); // Set serial port to read data until newline character

  // Initialize the positions
  x = width / 2;
  y = height / 2;
  prevX = x;
  prevY = y;
}

void draw() {
  // Drawing the line from the previous position to the current position
  stroke(0,0,0,20);
  //line(prevX, prevY, x, y);

  // Updating the previous position
  prevX = x;
  prevY = y;
  
  // Draw the circle at the current position
  fill(255, 0, 0, 20);
  noStroke();
  ellipse(x, y, 30, 30);
}

void serialEvent(Serial myPort) {
  // Reading the serial data
  inputData = myPort.readStringUntil('\n');
  inputData = inputData.trim(); // Remove any whitespace

  if (inputData != null && inputData.contains(",")) {
    // Split the incoming data into x and y components
    String[] coordinates = inputData.split(",");
    println(coordinates);
    if(coordinates.length == 2) {
      // Update the x and y coordinates
      x = map(float(coordinates[0]), minValueX, maxValueX, 0, width);
      y = map(float(coordinates[1]), minValueY, maxValueY, 0, height);
      //println(x,",",y);
    }
  }
}
