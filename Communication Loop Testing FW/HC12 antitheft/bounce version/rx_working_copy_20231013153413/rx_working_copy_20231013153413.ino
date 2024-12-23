#include <SoftwareSerial.h>

SoftwareSerial hc12Serial(10, 11); // RX, TX
const int ledPin = 4; // LED pin
const unsigned long timeoutPeriod = 5000; // Timeout period in milliseconds (5 seconds)

unsigned long lastCommandTime = 0; // Variable to store the timestamp of the last received command

void setup() {
  Serial.begin(9600);
  hc12Serial.begin(1200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (hc12Serial.available()) {
    String command = hc12Serial.readStringUntil('\n');
    command.trim(); // Remove leading/trailing whitespaces
    
    if (command == "on") {
      // Turn on the LED
      digitalWrite(ledPin, HIGH);
      Serial.println("Received: on - LED ON");
      lastCommandTime = millis(); // Update the last received command timestamp
    } else if (command == "off") {
      // Turn off the LED
      digitalWrite(ledPin, LOW);
      Serial.println("Received: off - LED OFF");
      lastCommandTime = millis(); // Update the last received command timestamp
    }
  }
  
  // Check for timeout and turn off the LED if needed
  if (millis() - lastCommandTime > timeoutPeriod) {
    digitalWrite(ledPin, LOW);
    Serial.println("Timeout - LED OFF");
    delay(1000);
  }
}