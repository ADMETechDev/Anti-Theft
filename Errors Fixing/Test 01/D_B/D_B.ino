#include <SoftwareSerial.h>

const int ledPin = 6;
const int buzzerPin = 7;
const int nomsPin = 8;
const int relay = 9;

int command;
bool systemOn = false;
unsigned long previousMillis = 0;
const long interval = 500;
const long blinkInterval = 1000; // Blink interval for nomsPin (milliseconds)
unsigned long nomsPreviousMillis = 0;
bool nomsState = false; // Track the state of nomsPin for blinking
SoftwareSerial HC12(10, 11); // RX, TX for HC-12

void setup() {
  Serial.begin(9600); // Initialize software serial communication with Serial Monitor
  HC12.begin(1200);   // Initialize software serial communication with HC-12
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(nomsPin, OUTPUT);
  pinMode(relay, OUTPUT);

  digitalWrite(ledPin, LOW); // Ensure LED is initially off
  noTone(buzzerPin);         // Ensure buzzer is initially off
  digitalWrite(nomsPin, LOW); // Ensure nomsPin is initially off
  digitalWrite(relay, HIGH);  // Ensure relay is initially off
}

void loop() {
  unsigned long currentMillis = millis();

  // Blink routine for nomsPin
  if (systemOn && currentMillis - nomsPreviousMillis >= blinkInterval) {
    nomsPreviousMillis = currentMillis;
    nomsState = !nomsState;
    digitalWrite(nomsPin, nomsState ? HIGH : LOW);
  }

  if (HC12.available() > 0) {
    command = HC12.read();  // Read data from Device B via HC-12
    if (command == '1') {
      digitalWrite(ledPin, HIGH);
      digitalWrite(relay, LOW);
      HC12.write('3'); // Send '3' to Device B via HC-12
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
          digitalWrite(relay, HIGH);
        } else {
          digitalWrite(nomsPin, HIGH);
          digitalWrite(relay, LOW);
        }
      } else {
        digitalWrite(ledPin, LOW);
        digitalWrite(nomsPin, LOW);
        digitalWrite(relay, HIGH);
        noTone(buzzerPin);
        systemOn = false;
      }
    }
  }

  if (Serial.available() > 0) {
    command = Serial.read();  // Read the command sent by the master via Serial Monitor
    // Handle incoming commands from the Serial Monitor if required (Not related to HC-12 communication)
  }
}
