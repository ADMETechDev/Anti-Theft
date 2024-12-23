// Device B
const int ledBPin = PIN_PB2;    // LED on Device B connected to PB2
bool ledBStatus = false;        // Status of the LED on Device B
bool connectionActive = false;  // Status of the connection with Device A

void setup() {
  Serial.swap(1);               // Swap pins for Serial communication
  Serial.begin(1200);           // Initialize serial communication at 1200 baud
  pinMode(ledBPin, OUTPUT);     // Configure LED pin as output
  digitalWrite(ledBPin, LOW);   // Ensure LED is off initially
}

void loop() {
  if (Serial.available() > 0) {  // Check if data is available
    char command = Serial.read();  // Read the incoming data
    if (command == '1') {
      ledBStatus = true;
      digitalWrite(ledBPin, HIGH); // Turn on the LED on Device B
      Serial.println('2');         // Send signal '2' back to Device A
      connectionActive = true;     // Assume connection is active after receiving
    } else if (command == '0') {
      connectionActive = false;    // Reset the connection status
      digitalWrite(ledBPin, LOW);  // Turn off the LED on Device B
      ledBStatus = false;          // Reset LED status
    }
  }

  if (!connectionActive) {
    digitalWrite(ledBPin, LOW);    // Ensure LED is off if connection is inactive
  }
}
