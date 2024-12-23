#include <SoftwareSerial.h>

const int TX_Pin = PIN_PA2;
const int RX_Pin = PIN_PA1;

SoftwareSerial HC12(TX_Pin, RX_Pin); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC-12
  
  Serial.println("Transmitter Ready");
}

void loop() {
  HC12.println("Hello Receiver!"); // Send a message to the receiver
  Serial.println("Message sent: Hello Receiver!");
  
  delay(1000); // Wait for 1 second

  if (HC12.available()) { // If there is data from the receiver
    String received = HC12.readString();
    Serial.print("Received from receiver: ");
    Serial.println(received);
  } else {
    Serial.println("No response from receiver.");
  }

  delay(3000); // Wait for 3 seconds before sending the next message
}