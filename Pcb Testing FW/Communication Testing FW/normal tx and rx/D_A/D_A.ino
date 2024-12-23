#include <SoftwareSerial.h>

// Define pins for HC-12
#define HC12_TX PIN_PA2  // TX pin of HC-12 connected to PA2
#define HC12_RX PIN_PA1  // RX pin of HC-12 connected to PA1

// Define pins for buttons
#define BUTTON1_PIN PIN_PA4  // Button 1 connected to PA3
#define BUTTON2_PIN PIN_PA5  // Button 2 connected to PA4

SoftwareSerial hc12(HC12_RX, HC12_TX); // Create SoftwareSerial object

void setup() {
  pinMode(BUTTON1_PIN, INPUT_PULLUP); // Button 1
  pinMode(BUTTON2_PIN, INPUT_PULLUP); // Button 2
  hc12.begin(9600); // Set HC-12 baud rate to 9600
}

void loop() {
  if (digitalRead(BUTTON1_PIN) == LOW) {
    hc12.println("LED_ON"); // Send command to turn on LED
    delay(300); // Debounce delay
  }

  if (digitalRead(BUTTON2_PIN) == LOW) {
    hc12.println("LED_OFF"); // Send command to turn off LED
    delay(300); // Debounce delay
  }
}
