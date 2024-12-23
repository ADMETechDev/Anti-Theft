#include <SoftwareSerial.h>

const int ledPin = 6;
const int buttonPin = 8;
const int buttonPin2 = 9;
const int buzzerPin = 7;

int command, active;
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
  
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, FALLING); // Attach interrupt to buttonPin
  attachInterrupt(digitalPinToInterrupt(buttonPin2), buttonReleased, FALLING); // Attach interrupt to buttonPin2
}

void loop() {
  if (HC12.available() > 0) {
    command = HC12.read();  // Read the command sent by Device A via HC-12
    if (command == '3') {
      digitalWrite(ledPin, HIGH);   // Turn on the LED
      digitalWrite(buzzerPin, HIGH);// Turn on the buzzer
      tone(buzzerPin, 1047);        // Generate a tone
      delay(200);
    } else {
      digitalWrite(ledPin, LOW);    // Turn off the LED
      noTone(buzzerPin);            // Turn off the buzzer
    }
  }

  if (active == 1) {
    HC12.write('1');  // Send '1' to Device A via HC-12
    delay(100);
  } else {
    digitalWrite(ledPin, LOW);    // Turn off the LED
    noTone(buzzerPin);            // Turn off the buzzer
  }
}

void buttonPressed() {
  active = 1;
}

void buttonReleased() {
  active = 0;
}
