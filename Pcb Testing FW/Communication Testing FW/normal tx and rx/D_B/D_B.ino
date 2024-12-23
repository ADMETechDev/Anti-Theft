#include <SoftwareSerial.h>

// Define pins for HC-12
#define HC12_TX PIN_PA2  // TX pin of HC-12 connected to PA2
#define HC12_RX PIN_PA1  // RX pin of HC-12 connected to PA1

// Define pin for LED
#define LED_PIN PIN_PB1  // LED connected to PA5

SoftwareSerial hc12(HC12_RX, HC12_TX); // Create SoftwareSerial object

void setup() {
  pinMode(LED_PIN, OUTPUT); // Initialize the LED pin as an output
  hc12.begin(9600); // Set HC-12 baud rate to 9600
}

void loop() {
  if (hc12.available()) {
    String command = hc12.readStringUntil('\n'); // Read the incoming command

    if (command == "LED_ON") {
      digitalWrite(LED_PIN, HIGH); // Turn on LED
    } else if (command == "LED_OFF") {
      digitalWrite(LED_PIN, LOW); // Turn off LED
    }
  }
}
