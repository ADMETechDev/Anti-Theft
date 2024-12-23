#include <SoftwareSerial.h>

SoftwareSerial HC12Serial(PIN_PA1, PIN_PA2); // RX, TX

void setup() {
  Serial.begin(9600);
  HC12Serial.begin(9600);
}

void loop() {
  HC12Serial.write("Hello from Device A!"); // Send command to Device B
  delay(1000);
  
  if (HC12Serial.available()) {
    Serial.println("Received confirmation from Device B:");
    while (HC12Serial.available()) {
      Serial.write(HC12Serial.read());
    }
    Serial.println();
  }
  delay(1000);
}
