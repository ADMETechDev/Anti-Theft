#include <SoftwareSerial.h>

const int ledPin = 4;
const int buttonPin = 2;
const int buttonPin2 = 3;
const int buzzerPin = 5;

int command, active;
SoftwareSerial HC12(10, 11); // RX, TX for HC-12

void setup() {
  Serial.begin(9600); // Initialize software serial communication with Serial Monitor
  HC12.begin(1200);   // Initialize software serial communication with HC-12
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();  // Read the command sent by the master
    if (command == '3') {
      digitalWrite(ledPin, HIGH);
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
  }
  if (digitalRead(buttonPin2) == LOW) {
    active = 0;
    delay(30);
  }

  if (active == 1) {
    HC12.write('1');  // Send '1' to Device B via HC-12
    delay(100);
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }

  if (HC12.available() > 0) {
    command = HC12.read();  // Read data from Device B via HC-12
    // Handle incoming commands from Device B if required
  }
}