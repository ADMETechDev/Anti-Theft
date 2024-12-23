// Device A
const int buttonPin = PIN_PA4;    // Button to turn on the connection
const int resetButtonPin = PIN_PA5; // Button to turn off the connection
const int ledAPin = PIN_PA7;      // LED on Device A connected to PB3
bool ledAStatus = false;          // Status of the LED on Device A
bool connectionActive = false;    // Status of the connection with Device B

void setup() {
  Serial.swap(1);                 // Swap pins for Serial communication
  Serial.begin(1200);             // Initialize serial communication at 1200 baud
  pinMode(buttonPin, INPUT_PULLUP);  // Configure button pin as input with pull-up
  pinMode(resetButtonPin, INPUT_PULLUP); // Configure reset button pin as input with pull-up
  pinMode(ledAPin, OUTPUT);       // Configure LED pin as output
  digitalWrite(ledAPin, LOW);     // Ensure LED is off initially
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {  // Check if the button is pressed to turn on connection
    Serial.println('1');                // Send signal '1' to Device B
    delay(100);                         // Debounce delay
    connectionActive = true;            // Assume connection is active after sending
  }

  if (digitalRead(resetButtonPin) == LOW) {  // Check if the reset button is pressed
    connectionActive = false;           // Reset the connection status
    Serial.println('0');                // Send signal '0' to Device B to turn off
    digitalWrite(ledAPin, LOW);         // Turn off the LED on Device A
    ledAStatus = false;                 // Reset LED status
    delay(100);                         // Debounce delay
  }

  if (Serial.available() > 0) {         // Check if data is available
    char response = Serial.read();      // Read the incoming data
    if (response == '2') {              // If response is '2', turn on LED
      ledAStatus = true;
      digitalWrite(ledAPin, HIGH);
    }
  }

  if (!connectionActive) {
    digitalWrite(ledAPin, LOW);         // Ensure LED is off if connection is inactive
  }
}
