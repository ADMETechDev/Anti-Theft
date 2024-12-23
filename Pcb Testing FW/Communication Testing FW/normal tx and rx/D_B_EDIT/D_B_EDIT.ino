#include <SoftwareSerial.h>

const int TX_Pin = PIN_PA2;
const int RX_Pin = PIN_PA1;

SoftwareSerial HC12(TX_Pin, RX_Pin); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC-12
  
  Serial.println("Receiver Ready");
}

void loop() {
  if (HC12.available()) { // If there is data from the transmitter
    String received = HC12.readString();
    Serial.print("Received from transmitter: ");
    Serial.println(received);

    HC12.println("Hello Transmitter!"); // Send a response back to the transmitter
    Serial.println("Response sent: Hello Transmitter!");
  }
}
