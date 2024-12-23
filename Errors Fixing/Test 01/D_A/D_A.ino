#include <SoftwareSerial.h>

const int ledPin = 6;
const int buttonPin = 8;
const int buttonPin2 = 9;
const int buzzerPin = 7;

int command, active;
bool button2Pressed = false; // Track if buttonPin2 is pressed
bool isBlinking = false; // Track if LED and buzzer are blinking

SoftwareSerial HC12(10, 11); // RX, TX for HC-12

void setup() {
  Serial.begin(9600); // Initialize software serial communication with Serial Monitor
  HC12.begin(1200);   // Initialize software serial communication with HC-12
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(ledPin, LOW);     // Ensure LED is initially off
  noTone(buzzerPin);             // Ensure buzzer is initially off
}

void loop() {
  if (HC12.available() > 0) {
    command = HC12.read();  // Read the command sent by Device A via HC-12
    if (command == '3') {
      digitalWrite(ledPin, HIGH);   // Turn on the LED
      digitalWrite(buzzerPin, HIGH);// Turn on the buzzer
      tone(buzzerPin, 1047);        // Generate a tone
      delay(200);
      isBlinking = true; // Start blinking
    } else {
      digitalWrite(ledPin, LOW);    // Turn off the LED
      noTone(buzzerPin);            // Turn off the buzzer
      isBlinking = false; // Stop blinking
    }
  }

  if (digitalRead(buttonPin) == LOW) {
    active = 1;
    delay(30);
  }
  
  // Check if buttonPin2 was pressed
  if (digitalRead(buttonPin2) == LOW && !button2Pressed) {
    button2Pressed = true;
    // Turn off LED and buzzer
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    // Send command to turn off Device B
    HC12.write('2');
    delay(30);
  }

  if (active == 1) {
    HC12.write('1');  // Send '1' to Device A via HC-12
    delay(100);
  } else {
    digitalWrite(ledPin, LOW);    // Turn off the LED
    noTone(buzzerPin);            // Turn off the buzzer
  }
}
