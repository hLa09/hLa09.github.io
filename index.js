// This should match the baud rate in your Arduino sketch
const BAUD_RATE = 9600;
// Declare global variables
let port, connectBtn;
// declare variable to store previous value of x position
let pX = 0;
// declare variable to store previous value of y position
let pY = 0;

// This function help setting up the webpage
function setup() {
  // Run our serial setup function (below)
  setupSerial();
  // Create a canvas that is the size of our browser window.
  // windowWidth and windowHeight are p5 variables
  createCanvas(windowWidth, windowHeight);
  // Creating a stroke like density of 4
  strokeWeight(4);
  // Adding stroke line color to distinct from the blackground
  stroke('#222222');
  // p5 text settings. BOLD and CENTER are constants provided by p5.
  // See the "Typography" section in the p5 reference: https://p5js.org/reference/
  textFont("system-ui", 50);
  textStyle(BOLD);
  textAlign(CENTER, CENTER);
}

function draw() {
  // Check whether the port is open (see checkPort function below)
  const portIsOpen = checkPort();
  // If the port is not open, exit the draw loop
  if (!portIsOpen) return;
  // Read from the port until the newline
  let str = port.readUntil("\n");
  // If we didn't read anything, return.
  if (str.length == 0) return;
  // Trim whitespace and split on commas
  let arr = str.trim().split(",");
  // Make the background white
  background('rgb(150, 248, 255)');

  // Convert each value from analogRead to a number, map it to the joystick range, and round to nearest integer
  // for example of serial passing in: 511, 509, then the value will be convert to the window's range
  const x = round(map(Number(arr[0]), 0, 1023, 0, 1470));
  const y = round(map(Number(arr[1]), 0, 1023, 0, 860));
  // text white
  fill('rgb(255, 255, 255)');
  // the size of the text display
  textSize(40);
  // Display text in order of x value, y value on the following coordinates of the window frame
  text(`${x}, ${y}`, 735, 75);
  fill('rgb(61, 36, 0)');
  circle(x, y, 50);
  // This help creating the line tracker, by loggin the previous position and current position
  console.log(pX);
  // check to see if previous x position is 0 or not
  if(pX == 0){
    // when prior x position is zero, update the position with the current position
    pX = x;
    // when prior y position is zero, update the position with the current position
    pY = y;
  } else{
    // when previous x position is not at 0, create a line that track the range of the position is in
    // previous x to current x, previous y to current y
    line(pX, pY, x, y);
    // updatign the previous x position
    pX = x;
    // updating the previous y position
    pY = y;
  }
  // When the Enter key on the keyboard is pressed
  if(keyIsDown(ENTER)){
    // write to the port char 1
    port.write('1');
  }
}

// Three helper functions for managing the serial connection.
function setupSerial() {
  port = createSerial();

  // Check to see if there are any ports we have used previously
  let usedPorts = usedSerialPorts();
  if (usedPorts.length > 0) {
    // If there are ports we've used, open the first one
    port.open(usedPorts[0], BAUD_RATE);
  }

  // create a connect button
  connectBtn = createButton("Connect to Arduino");
  connectBtn.position(5, 5); // Position the button in the top left of the screen.
  connectBtn.mouseClicked(onConnectButtonClicked); // When the button is clicked, run the onConnectButtonClicked function
}

function checkPort() {
  if (!port.opened()) {
    // If the port is not open, change button text
    connectBtn.html("Connect to Arduino");
    // Set background to gray
    background("gray");
    return false;
  } else {
    // Otherwise we are connected
    connectBtn.html("Disconnect");
    return true;
  }
}

function onConnectButtonClicked() {
  // When the connect button is clicked
  if (!port.opened()) {
    // If the port is not opened, we open it
    port.open(BAUD_RATE);
  } else {
    // Otherwise, we close it!
    port.close();
  }
}
