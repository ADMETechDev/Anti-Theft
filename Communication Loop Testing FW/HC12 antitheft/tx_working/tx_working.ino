#include <SoftwareSerial.h>

SoftwareSerial hc12Serial(10, 11); // TX, RX
const int buttonPin = 7; // Button pin

void setup() {
  Serial.begin(9600);
  hc12Serial.begin(1200);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    // Button is pressed, send "on" command
    hc12Serial.println("on");
    Serial.println("Sent: on");
  } else {
    // Button is released, send "off" command
    hc12Serial.println("off");
    Serial.println("Sent: off");
  }
  delay(500); // Add a delay to avoid sending multiple commands quickly
}
