#include <SoftwareSerial.h>

const int ledPin = 6;      // LED connected to digital pin 6
const int buttonPin = 7;
const int buttonPin2 = 8;
const int buzzerPin = 9;

SoftwareSerial HC12(10, 11); // RX, TX pins for HC-12 communication

int command, active;

void setup() {
  Serial.begin(9600);    // Initialize serial communication with computer
  HC12.begin(9600);      // Initialize HC-12 communication
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();  // Read the command sent by the master
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
    HC12.write('1');  // Send '1' to the other device via HC-12
  }

  if (digitalRead(buttonPin2) == LOW) {
    active = 0;
    delay(30);
    HC12.write('0');  // Send '0' to the other device via HC-12
  }

  if (HC12.available() > 0) {
    command = HC12.read();  // Read data received from the other device via HC-12
    if (command == '1') {
      Serial.println('1');  // Send '1' to the master via serial communication
      delay(100);
    }
  }
}
