// Define the pin for the buzzer
const int buzzerPin = PIN_PB3; // Change this to the pin where your buzzer is connected

void setup() {
  // Set the buzzer pin as an output
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  tone(buzzerPin, 1047, 100);
      //delay(100);
  tone(buzzerPin, 1760, 200);
      //delay(200);
  
  // Turn the buzzer off
  digitalWrite(buzzerPin, LOW);
  delay(1000); // Wait for 1 second
}
