#include <SoftwareSerial.h>

SoftwareSerial HC12Serial(PIN_PA1, PIN_PA2); // RX, TX

void setup() {
  Serial.begin(9600);
  HC12Serial.begin(9600);
}

void loop() {
  if (HC12Serial.available()) {
    Serial.println("Received command from Device A:");
    while (HC12Serial.available()) {
      Serial.write(HC12Serial.read());
    }
    Serial.println();
    
    HC12Serial.write("Signal Received!"); // Send confirmation to Device A
    delay(1000);
  }
}
