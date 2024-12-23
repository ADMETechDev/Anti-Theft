#include <SoftwareSerial.h>

const int ledPin = 6;
const int buzzerPin = 7;
const int nomsPin = 8;

SoftwareSerial HC12(10, 11);  // RX, TX pins for HC-12 communication

int command;
bool systemOn = false;
unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(nomsPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (HC12.available() > 0) {
    command = HC12.read();
    if (command == '1') {
      digitalWrite(ledPin, HIGH);
      Serial.write('3');
      tone(buzzerPin, 1047, 100);
      delay(100);
      tone(buzzerPin, 1760, 200);
      delay(200);
      digitalWrite(ledPin, LOW);
      digitalWrite(nomsPin, HIGH);
      previousMillis = currentMillis;
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
    command = Serial.read();
    if (command == '3') {
      digitalWrite(ledPin, HIGH);
      tone(buzzerPin, 1047);
      delay(200);
    } else {
      digitalWrite(ledPin, LOW);
      noTone(buzzerPin);
    }
  }

  if (HC12.available() > 0) {
    command = HC12.read();
    if (command == '1') {
      Serial.println('1');
      delay(100);
    }
  }
}
