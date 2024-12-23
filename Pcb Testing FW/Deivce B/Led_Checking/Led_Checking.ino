// Define the pins for the LEDs
const int ledPin1 = PIN_PB1; // Pin for LED 1
const int ledPin2 = PIN_PB2; // Pin for LED 2

void setup() {
  // Set the LED pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  // Turn LED 1 on, LED 2 off
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, LOW);
  delay(1000); // Wait for 1 second
  
  // Turn LED 1 off, LED 2 on
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, HIGH);
  delay(1000); // Wait for 1 second
}

