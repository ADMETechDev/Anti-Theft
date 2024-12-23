#include <SoftwareSerial.h>

const int ledPin = 6;      // LED connected to digital pin 6
const int buttonPin = 7;
const int buttonPin2 = 8;
const int buzzerPin = 9;

int command, active;
SoftwareSerial HC12(10, 11); // RX, TX pins for HC-12 communication

void setup() {
  Serial.begin(9600);  // Initialize serial monitor
  HC12.begin(9600);    // Initialize HC-12 communication
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (HC12.available() > 0) {
    command = HC12.read();  // Read the command sent by the HC-12 module
    if (command == '3') {
      digitalWrite(ledPin, HIGH);  // Turn the LED on
      tone(buzzerPin, 1047);
      delay(200); 
    } else {
      digitalWrite(ledPin, LOW);
      noTone(buzzerPin);
    }
  }

  if (digitalRead(buttonPin) == LOW) {
    active = 1;
    delay(30);
    HC12.write('1');  // Send '1' when buttonPin is pressed
  }

  if (digitalRead(buttonPin2) == LOW) {
    active = 0;
    delay(30);
    HC12.write('0');  // Send '0' when buttonPin2 is pressed
  }

  if (active == 1) {
    Serial.println('1');
    delay(100);
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }
}
