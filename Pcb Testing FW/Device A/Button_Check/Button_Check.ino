// Define the pins for the LEDs
const int ledPin1 = PIN_PA6; // Pin for LED 1
const int ledPin2 = PIN_PA7; // Pin for LED 2

// Define the pins for the buttons
const int buttonPin1 = PIN_PA4; // Pin for Button 1
const int buttonPin2 = PIN_PA5; // Pin for Button 2

void setup() {
  // Set the LED pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // Set the button pins as inputs with internal pull-up resistors
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  // Ensure LEDs are initially off
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
}

void loop() {
  // Read the state of the buttons
  bool button1State = digitalRead(buttonPin1);
  bool button2State = digitalRead(buttonPin2);

  // Check if button 1 is pressed (active low)
  if (button1State == LOW) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
  }

  // Check if button 2 is pressed (active low)
  if (button2State == LOW) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  }
}
