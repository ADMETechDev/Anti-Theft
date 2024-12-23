#include <SoftwareSerial.h>

SoftwareSerial hc12Serial(10, 11); // RX, TX
const int buttonPin = 4; // Button pin
const int transmitterLedPin = 5; // LED pin on the transmitter

void setup() {
  Serial.begin(9600);
  hc12Serial.begin(1200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(transmitterLedPin, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    // Button is pressed, send "on" command
    hc12Serial.println("on");
    Serial.println("Sent: on");
    delay(1000); // Wait for a moment to avoid multiple transmissions
  } else {
    // Button is released, send "off" command
    hc12Serial.println("off");
    Serial.println("Sent: off");
    delay(1000); // Wait for a moment to avoid multiple transmissions
  }
  
  // Check if the transmitter receives the same signal back from the receiver
  if (hc12Serial.available()) {
    String response = hc12Serial.readStringUntil('\n');
    response.trim();
    if (response == "on" || response == "off") {
      digitalWrite(transmitterLedPin, HIGH); // Turn on the LED on the transmitter
      delay(1000); // Wait for a moment to keep the LED on
      digitalWrite(transmitterLedPin, LOW); // Turn off the LED on the transmitter
    }
  }
}