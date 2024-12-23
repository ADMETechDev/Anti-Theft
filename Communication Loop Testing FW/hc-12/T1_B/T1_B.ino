#include <SoftwareSerial.h>

const int ledPin = 6;    // LED connected to digital pin 6
const int buzzerPin = 7;
const int nomsPin = 8;
int command;
bool systemOn = false;
unsigned long previousMillis = 0;
const long interval = 500;

SoftwareSerial HC12(10, 11); // RX, TX pins for HC-12 communication

void setup() {
  Serial.begin(9600);  // Initialize serial communication with the computer
  HC12.begin(9600);    // Initialize HC-12 communication
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(nomsPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (HC12.available() > 0) {
    command = HC12.read();  // Read the command sent by the HC-12 module
    if (command == '1') {
      digitalWrite(ledPin, HIGH);
      Serial.write('3');  // Respond to the master via the computer's serial port
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
        // Blink the nomsPin LED within the specified interval
        if ((currentMillis / 100) % 2 == 0) {
          digitalWrite(nomsPin, LOW);
        } else {
          digitalWrite(nomsPin, HIGH);
        }
      } else {
        // Turn off the nomsPin LED after the interval
        digitalWrite(ledPin, LOW);
        digitalWrite(nomsPin, LOW);
        noTone(buzzerPin);
        systemOn = false;
      }
    }
  }
}
