// Device B
const int ledBPin = PIN_PB2;    // LED on Device B connected to PB2

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
      digitalWrite(ledBPin, HIGH); // Turn on the LED on Device B
      Serial.println('2');         // Send signal '2' back to Device A
    }
  }
}
