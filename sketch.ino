
// Variable that will be connect to a pin on the Arduino
// unchange variables.
// this is to define red LED pin
const int pinR = 2;
// this is to define yellow LED pin
const int pinY = 4;
// this is to define white LED pin
const int pinW = 7;
// this is to define green LED pin
const int pinB = 12;
// this is to define blue LED pin
const int pinG = 13;
// this will define the VRX pin from the joystick connect to the Arduino
const int x = A1;
// this will define the VRY pin from the joystick connect to the Arduino
const int y = A0;

// Declaring a constant minimum center range, as the joystick x, and y axis tend to land around 509 to 515
int center_range_min = 500;
// Declaring a constant maximum center range, as the joystick x, and y axis tend to land around 509 to 515
int center_range_max = 515;

// Variable will be change due to input
// to store value of the x-axis, when analog to the reading of x.
int xVal = 0;
// to store value of the y-axis, when analog to the reading of y.
int yVal = 0;

// This method help setup the function needed
void setup() {
  // set pinMode for LEDs:
  // pinMode for Red LED as an output
  pinMode(pinR, OUTPUT);
  // pinMode for Yellow LED as an output
  pinMode(pinY, OUTPUT);
  // pinMode for White LED as an output
  pinMode(pinW, OUTPUT);
  // pinMode for Green LED as an output
  pinMode(pinB, OUTPUT);
  // pinMode for Blue LED as an output
  pinMode(pinG, OUTPUT);

  // Setting up serial communication
  Serial.begin(9600);
  // Set a timeout for parseInt
  Serial.setTimeout(10);

}

void loop() {
  // put your main code here, to run repeatedly:
  // check to see if there is serial data
  if (Serial.available() > 0) {
    // read the serial data
    int value = Serial.read();
    // send the value back as raw binary data
    Serial.write(value);
    // Making the White LED blink
    // turn on the White LED when there is data to parse
    digitalWrite(pinW, HIGH);
    // delay the LED on for 300 milliseconds
    delay(300);
    // turn the White LED off after 300 milliseconds
    digitalWrite(pinW, LOW);
  }
  // delaying before moving forward to other code, avoid glitching.
  delay(100);

  // This read the analog X values
  xVal = analogRead(x);
  // This read the analog Y values
  yVal = analogRead(y);

  // Checking for the x and y range:
  // when x value is less than center minimmum range and
  // y value is between the origin range
  // this indicate that the joystick get push towards the left direction
  // When the joystick is tilting to the left, Red LED turn on.
  if (xVal < center_range_min &&
  yVal >= center_range_min && yVal <= center_range_max){
    // turn the Red LED on by setting it as HIGH
    digitalWrite(pinR, HIGH);
    // turn the Yellow LED off by setting it as LOW
    digitalWrite(pinY, LOW);
    // turn the Blue LED off by setting it as LOW
    digitalWrite(pinB, LOW);
    // turn the Green LED off by setting it as LOW
    digitalWrite(pinG, LOW);
  }
  // Checking for the x and y range:
  // when x value is greater than center maximmum range and
  // y value is between the origin range
  // this indicate that the joystick get push in the right direction
  // When the joystick is tilting to the right, Yellow LED turn on.
  else if(xVal > center_range_max &&
  yVal >= center_range_min && yVal <= center_range_max){
    // turn the Yellow LED on by setting it as HIGH
    digitalWrite(pinY, HIGH);
    // turn the Red LED off by setting it as LOW
    digitalWrite(pinR, LOW);
    // turn the Blue LED off by setting it as LOW
    digitalWrite(pinB, LOW);
    // turn the Green LED off by setting it as LOW
    digitalWrite(pinG, LOW);
  }
  // Checking for the x and y range:
  // when y value is greater than center maximmum range and
  // x value is between the origin range
  // this indicate that the joystick get push in the downward direction
  // When the joystick is in the downward direction, Blue LED turn on.
  else if (yVal > center_range_max &&
  xVal >= center_range_min && xVal <= center_range_max){
    // turn the Blue LED on by setting it as HIGH
    digitalWrite(pinB, HIGH);
    // turn the Yellow LED off by setting it as LOW
    digitalWrite(pinY, LOW);
    // turn the Red LED off by setting it as LOW
    digitalWrite(pinR, LOW);
    // turn the Green LED off by setting it as LOW
    digitalWrite(pinG, LOW);
  }
  // Checking for the x and y range:
  // when y value is less than center minimum range and
  // x value is between the origin range
  // this indicate that the joystick get push in the upward direction.
  // When the joystick is in the upward direction, Green LED turn on.
  else if(yVal < center_range_min &&
  xVal >= center_range_min && xVal <= center_range_max){
    // turn the Green LED on by setting it as HIGH
    digitalWrite(pinG, HIGH);
    // turn the Yellow LED off by setting it as LOW
    digitalWrite(pinY, LOW);
    // turn the Blue LED off by setting it as LOW
    digitalWrite(pinB, LOW);
    // turn the Red LED off by setting it as LOW
    digitalWrite(pinR, LOW);
  }
  // turn all LEDs off when the joystick is centered
  else {
    // turn the Green LED off by setting it as LOW
    digitalWrite(pinG, LOW);
    // turn the Yellow LED off by setting it as LOW
    digitalWrite(pinY, LOW);
    // turn the Blue LED off by setting it as LOW
    digitalWrite(pinB, LOW);
    // turn the Red LED off by setting it as LOW
    digitalWrite(pinR, LOW);
  }


  // Print the x value from analogRead() for x position to serial array
  Serial.print(xVal);
  // separating the x and y value
  Serial.print(", ");
  // Print the y value reading from analogRead() for y position to serial array
  Serial.println(yVal);

  // Delaying for 10 millisecond to avoid glitching
  delay(100);

}
