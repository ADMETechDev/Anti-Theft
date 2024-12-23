#include <SoftwareSerial.h>

// Define pins for HC-12
#define HC12_TX PIN_PA2 // TX pin of HC-12 connected to PA2
#define HC12_RX PIN_PA1 // RX pin of HC-12 connected to PA1

SoftwareSerial HC12(HC12_RX, HC12_TX); // Create SoftwareSerial object

void setup() {
  Serial.begin(9600); // Initialize serial communication with Serial Monitor
  HC12.begin(1200);   // Initialize software serial communication with HC-12
  delay(1000);        // Give some time for HC-12 to initialize
}

void loop() {
  if (HC12.available() > 0) {
    String receivedMessage = HC12.readStringUntil('\n'); // Read the incoming message
    Serial.print("Received: "); 
    Serial.println(receivedMessage); // Print the received message to the Serial Monitor

    if (receivedMessage == "Hello World") {
      HC12.println("Hello from Device B"); // Send response message to Device A
      Serial.println("Sent: Hello from Device B"); // Print the response message to the Serial Monitor
    }
  }

  delay(1000); // Wait for 1 second before checking for new messages
}
