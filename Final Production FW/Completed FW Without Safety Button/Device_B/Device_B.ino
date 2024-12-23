// Device B
const int ledBPin = PIN_PB2;    // LED on Device B connected to PB2
const int buzzerPin = PIN_PB3;
const int relayPin = PIN_PC1;

bool connectionActive = false;  // Status of the connection with Device A
bool disconnectedFlag = false;  // Flag to check if disconnection occurred
unsigned long lastReceivedTime = 0;  // Last time a signal was received
const unsigned long timeoutDuration = 3000; // Timeout duration in milliseconds (3 seconds)

void setup() {
  Serial.swap(1);               // Swap pins for Serial communication
  Serial.begin(1200);           // Initialize serial communication at 1200 baud
  pinMode(ledBPin, OUTPUT);     // Configure LED pin as output
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(ledBPin, LOW);   // Ensure LED is off initially
  digitalWrite(relayPin, HIGH);
}

void loop() {
  if (Serial.available() > 0) {  // Check if data is available
    char command = Serial.read();  // Read the incoming data
    if (command == '1') {
      digitalWrite(ledBPin, HIGH); // Turn on the LED on Device B
      digitalWrite(relayPin, LOW);
      tone(buzzerPin, 1047, 100);
      delay(100);
      tone(buzzerPin, 1760, 200);
      delay(100);
      Serial.println('2');         // Send signal '2' back to Device A
      connectionActive = true;     // Assume connection is active after receiving
      disconnectedFlag = false;    // Reset disconnection flag
      lastReceivedTime = millis(); // Update the last received time
    } else if (command == '0') {
      connectionActive = false;    // Reset the connection status
      disconnectedFlag = true;     // Set the disconnection flag
      digitalWrite(ledBPin, LOW);  // Turn off the LED on Device B
      digitalWrite(relayPin, HIGH);
      noTone(buzzerPin);
    }
  }

  // Check if connection timeout has occurred
  if (connectionActive && millis() - lastReceivedTime > timeoutDuration) {
    connectionActive = false;       // Reset connection status
    disconnectedFlag = true;        // Set disconnection flag
    digitalWrite(ledBPin, LOW);     // Turn off the LED on Device B
    digitalWrite(relayPin, HIGH);
    noTone(buzzerPin);
  }
}
