// Device A
const int buttonPin = PIN_PA4;  // Button connected to PA4
const int ledAPin = PIN_PA7;    // LED on Device A connected to PB3

void setup() {
  Serial.swap(1);               // Swap pins for Serial communication
  Serial.begin(1200);           // Initialize serial communication at 1200 baud
  pinMode(buttonPin, INPUT_PULLUP);  // Configure button pin as input with pull-up
  pinMode(ledAPin, OUTPUT);     // Configure LED pin as output
  digitalWrite(ledAPin, LOW);   // Ensure LED is off initially

  Serial.println("Device A ready");  // Debugging output
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {  // Check if the button is pressed
    Serial.println('1');                // Send signal '1' to Device B
    delay(100);                         // Debounce delay
    Serial.println("Sent '1' to Device B");  // Debugging output
  }

  if (Serial.available() > 0) {         // Check if data is available
    char response = Serial.read();      // Read the incoming data
    if (response == '2') {              // If response is '2', turn on LED
      digitalWrite(ledAPin, HIGH);
      Serial.println("Received '2' from Device B");  // Debugging output
    } else {
      digitalWrite(ledAPin, LOW);       // Keep LED off if no valid response
    }
  } else {
    digitalWrite(ledAPin, LOW);         // Keep LED off if no data is available
  }
}

