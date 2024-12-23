// Device A
const int buttonPin = PIN_PA4;    // Button to turn on the connection
const int buttonPin2 = PIN_PA5;   // Button to turn off the connection
const int ledAPin = PIN_PA7;      // LED on Device A connected to PA7
const int ledPin3 = PIN_PB3;
const int buzzerPin = PIN_PC2;

bool connectionActive = false;    // Status of the connection with Device B
unsigned long lastSendTime = 0;   // Last time a command was sent
const unsigned long sendInterval = 500; // Interval between sending commands (500ms)
const unsigned long timeoutDuration = 3000; // Timeout duration in milliseconds (3 seconds)
unsigned long lastReceivedTime = 0;  // Last time a signal was received

void setup() {
  Serial.swap(1);                 // Swap pins for Serial communication
  Serial.begin(1200);             // Initialize serial communication at 1200 baud
  pinMode(buttonPin, INPUT_PULLUP);  // Configure button pin as input with pull-up
  pinMode(buttonPin2, INPUT_PULLUP); // Configure reset button pin as input with pull-up
  pinMode(ledAPin, OUTPUT);       // Configure LED pin as output
  pinMode(ledPin3, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(ledAPin, LOW);     // Ensure LED is off initially
  digitalWrite(ledPin3, LOW);
}

void loop() {
  // Check if the button is pressed to turn on the connection
  if (digitalRead(buttonPin) == LOW && !connectionActive) {
    connectionActive = true;            // Activate the connection
    lastSendTime = millis();            // Update the last send time
    lastReceivedTime = millis();        // Update the last received time
    delay(100);                         // Debounce delay
  }

  // Check if the reset button is pressed
  if (digitalRead(buttonPin2) == LOW) {
    connectionActive = false;           // Reset the connection status
    Serial.println('0');                // Send signal '0' to Device B to turn off
    digitalWrite(ledAPin, LOW);         // Turn off the LED on Device A
    digitalWrite(ledPin3, LOW);
    noTone(buzzerPin);
    delay(100);                         // Debounce delay
  }

  // Send signal '1' to Device B only if connection is active
  if (connectionActive && millis() - lastSendTime > sendInterval) {
    Serial.println('1');                // Send signal '1' to Device B
    lastSendTime = millis();            // Update the last send time
  }

  // Check if data is available
  if (Serial.available() > 0) {
    char response = Serial.read();      // Read the incoming data
    if (response == '2' && connectionActive) {  // If response is '2', and connection is active
      digitalWrite(ledAPin, HIGH);
      digitalWrite(ledPin3, HIGH);
      tone(buzzerPin, 1047);
      lastReceivedTime = millis();      // Update the last received time
    }
  }

  // Check if connection timeout has occurred
  if (connectionActive && millis() - lastReceivedTime > timeoutDuration) {
    connectionActive = false;           // Reset connection status
    digitalWrite(ledAPin, LOW);         // Turn off the LED on Device A
    digitalWrite(ledPin3, LOW);
    noTone(buzzerPin);
  }
}
