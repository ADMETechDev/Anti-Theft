#include <SoftwareSerial.h>

const int ledPin = 4;
const int buzzerPin = 5;
const int nomsPin = 3;

int command;
bool systemOn = false;
unsigned long previousMillis = 0;
const long interval = 500;
SoftwareSerial HC12(10, 11); // RX, TX for HC-12

void setup() {
  Serial.begin(9600); // Initialize software serial communication with Serial Monitor
  HC12.begin(1200);   // Initialize software serial communication with HC-12
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(nomsPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (HC12.available() > 0) {
    command = HC12.read();  // Read data from Device A via HC-12
    if (command == '1') {
      digitalWrite(ledPin, HIGH);
      HC12.write('3'); // Send '3' to Device A via HC-12
      tone(buzzerPin, 1047, 100);
      delay(100);
      tone(buzzerPin, 1760, 200);
      delay(200);
      digitalWrite(ledPin, LOW);
      digitalWrite(nomsPin, HIGH);
      previousMillis = currentMillis;  // Reset the timer when signal is received
      systemOn = true;
    }
  } else {
    if (systemOn) {
      if (currentMillis - previousMillis < interval) {
        if ((currentMillis / 100) % 2 == 0) {
          digitalWrite(nomsPin, LOW);
        } else {
          digitalWrite(nomsPin, HIGH);
        }
      } else {
        digitalWrite(ledPin, LOW);
        digitalWrite(nomsPin, LOW);
        noTone(buzzerPin);
        systemOn = false;
      }
    }
  }

  if (Serial.available() > 0) {
    command = Serial.read();  // Read the command sent by the master
    // Handle incoming commands from Device A via Serial Monitor if required
  }
}

