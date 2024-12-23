// Device A
const int buttonPin = PIN_PA4;    // Button to turn on the connection
const int resetButtonPin = PIN_PA5; // Button to turn off the connection
const int ledAPin = PIN_PA7;      // LED on Device A connected to PA7
bool connectionActive = false;    // Status of the connection with Device B
unsigned long lastSendTime = 0;   // Last time a command was sent
const unsigned long sendInterval = 500; // Interval between sending commands (500ms)
const unsigned long timeoutDuration = 3000; // Timeout duration in milliseconds (3 seconds)
unsigned long lastReceivedTime = 0;  // Last time a signal was received

void setup() {
  Serial.swap(1);                 // Swap pins for Serial communication
  Serial.begin(1200);             // Initialize serial communication at 1200 baud
  pinMode(buttonPin, INPUT_PULLUP);  // Configure button pin as input with pull-up
  pinMode(resetButtonPin, INPUT_PULLUP); // Configure reset button pin as input with pull-up
  pinMode(ledAPin, OUTPUT);       // Configure LED pin as output
  digitalWrite(ledAPin, LOW);     // Ensure LED is off initially
}

void loop() {
  if (digitalRead(buttonPin) == LOW && !connectionActive) {  // Check if the button is pressed to turn on connection
    connectionActive = true;            // Activate the connection
    lastSendTime = millis();            // Update the last send time
    lastReceivedTime = millis();        // Update the last received time
    delay(100);                         // Debounce delay
  }

  if (digitalRead(resetButtonPin) == LOW) {  // Check if the reset button is pressed
    connectionActive = false;           // Reset the connection status
    Serial.println('0');                // Send signal '0' to Device B to turn off
    digitalWrite(ledAPin, LOW);         // Turn off the LED on Device A
    delay(100);                         // Debounce delay
  }

  if (connectionActive && millis() - lastSendTime > sendInterval) {
    Serial.println('1');                // Send signal '1' to Device B repeatedly
    lastSendTime = millis();            // Update the last send time
  }

  if (Serial.available() > 0) {         // Check if data is available
    char response = Serial.read();      // Read the incoming data
    if (response == '2') {              // If response is '2', turn on LED
      digitalWrite(ledAPin, HIGH);
      lastReceivedTime = millis();      // Update the last received time
    }
  }

  // Check if connection timeout has occurred
  if (connectionActive && millis() - lastReceivedTime > timeoutDuration) {
    connectionActive = false;           // Reset connection status
    digitalWrite(ledAPin, LOW);         // Turn off the LED on Device A
  }
}

