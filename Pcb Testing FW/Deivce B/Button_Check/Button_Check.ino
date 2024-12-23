// Define the pins for the LEDs
const int ledPin1 = PIN_PB1; // Pin for LED 1
const int ledPin2 = PIN_PB2; // Pin for LED 2

// Define the pin for the button
const int buttonPin = PIN_PC2; // Pin for the Button

// Variable to store the LED state
bool ledsOn = false;

// Variable to store the previous button state
bool lastButtonState = HIGH;

void setup() {
  // Set the LED pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // Set the button pin as input with internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Ensure LEDs are initially off
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
}

void loop() {
  // Read the state of the button
  bool buttonState = digitalRead(buttonPin);

  // Check if the button was pressed
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Toggle the LED state
    ledsOn = !ledsOn;

    // Update the LEDs based on the new state
    if (ledsOn) {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);
    } else {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
    }

    // Debounce delay
    delay(50); // Small delay to debounce the button
  }

  // Update the last button state
  lastButtonState = buttonState;
}
