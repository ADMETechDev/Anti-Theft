// Device A
const int buttonPin = PIN_PA4;    // Button to turn on the connection
const int buttonPin2 = PIN_PA5;   // Button to turn off the connection
const int buttonPin3 = PIN_PB5;
const int ledAPin = PIN_PA7;      // LED on Device A connected to PA7
const int ledPin3 = PIN_PB3;
const int buzzerPin = PIN_PC2;

bool connectionActive = false;    // Status of the connection with Device B
bool disconnectedFlag = false;    // Flag to check if disconnection occurred
unsigned long lastSendTime = 0;   // Last time a command was sent
const unsigned long sendInterval = 500; // Interval between sending commands (500ms)
const unsigned long timeoutDuration = 3000; // Timeout duration in milliseconds (3 seconds)
unsigned long lastReceivedTime = 0;  // Last time a signal was received

void setup() {
  Serial.swap(1);                 // Swap pins for Serial communication
  Serial.begin(1200);             // Initialize serial communication at 1200 baud
  pinMode(buttonPin, INPUT_PULLUP);  // Configure button pin as input with pull-up
  pinMode(buttonPin2, INPUT_PULLUP); // Configure reset button pin as input with pull-up
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(ledAPin, OUTPUT);       // Configure LED pin as output
  pinMode(ledPin3, OUTPUT);
  pinMode(buzzerPin, INPUT);
  digitalWrite(ledAPin, LOW);     // Ensure LED is off initially
  digitalWrite(ledPin3, LOW);
}

void loop() {
  // If button is pressed on Device A and disconnection occurred, reset the connection
  if (digitalRead(buttonPin) == LOW && (digitalRead(buttonPin3) == LOW) && !connectionActive && disconnectedFlag) {
    connectionActive = true;            // Activate the connection
    disconnectedFlag = false;           // Reset the disconnection flag
    lastSendTime = millis();            // Update the last send time
    lastReceivedTime = millis();        // Update the last received time
    delay(50);                         // Debounce delay
  }

  // If the reset button is pressed, turn off the connection and set the disconnection flag
  if ((digitalRead(buttonPin2) == LOW) && (digitalRead(buttonPin3) == LOW)) {  // Check if the reset button is pressed
    connectionActive = false;           // Reset the connection status
    disconnectedFlag = true;            // Set the disconnection flag
    Serial.println('0');                // Send signal '0' to Device B to turn off
    digitalWrite(ledAPin, LOW);         // Turn off the LED on Device A
    digitalWrite(ledPin3, LOW);
    noTone(buzzerPin);
    delay(100);                         // Debounce delay
  }

  // Regularly send signals if the connection is active
  if (connectionActive && millis() - lastSendTime > sendInterval) {
    //Serial.println('1');                // Send signal '1' to Device B
    lastSendTime = millis();            // Update the last send time
  }

  // Handle incoming serial data
  if (Serial.available() > 0) {         // Check if data is available
    char response = Serial.read();      // Read the incoming data
    if (response == '2') {              // If response is '2', turn on LED
      digitalWrite(ledAPin, HIGH);
      digitalWrite(ledPin3, HIGH);
     //digitalWrite(buzzerPin, HIGH);
      tone(buzzerPin, 1047);
      lastReceivedTime = millis();      // Update the last received time
    }
  }

  // Check if connection timeout has occurred
  if (connectionActive && millis() - lastReceivedTime > timeoutDuration) {
    connectionActive = false;           // Reset connection status
    disconnectedFlag = true;            // Set the disconnection flag
    digitalWrite(ledAPin, LOW);         // Turn off the LED on Device A
    digitalWrite(ledPin3, LOW);
    noTone(buzzerPin);
  }
}

