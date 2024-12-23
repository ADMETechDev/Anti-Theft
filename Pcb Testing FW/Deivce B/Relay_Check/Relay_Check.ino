const int relayPin = PIN_PC1; // Pin connected to the relay
const int delayTime = 1000;   // Time in milliseconds to wait between toggles

void setup() {
  // Initialize the serial communication for debugging
  Serial.begin(9600);

  // Set the relay pin as output
  pinMode(relayPin, OUTPUT);

  // Ensure relay is initially off
  digitalWrite(relayPin, LOW);

  Serial.println("Relay test started...");
}

void loop() {
  // Turn the relay on (and thus the LED strip)
  digitalWrite(relayPin, HIGH);
  Serial.println("Relay ON - LED strip should be ON");
  delay(delayTime); // Wait for a second

  // Turn the relay off (and thus the LED strip)
  digitalWrite(relayPin, LOW);
  Serial.println("Relay OFF - LED strip should be OFF");
  delay(delayTime); // Wait for a second
}

