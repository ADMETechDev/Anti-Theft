#define BATTERY_PIN PIN_PA4 // Analog pin to read the battery voltage
#define ENABLE_PIN PIN_PA7 // GPIO pin to enable battery voltage measurement
#define MAX_VOLTAGE 4.2 // Maximum voltage of a fully charged battery (Li-ion typically 4.2V)
#define MIN_VOLTAGE 3.0 // Minimum voltage of a discharged battery (Li-ion typically 3.0V)

void setup() {
  Serial.begin(115200); // Start the serial communication at 115200 baud rate
  pinMode(ENABLE_PIN, OUTPUT); // Set the enable pin as an output
  digitalWrite(ENABLE_PIN, LOW); // Initially disable the battery measurement
  delay(1000); // Wait for serial communication to start
}

void loop() {
  digitalWrite(ENABLE_PIN, HIGH); // Enable battery voltage measurement
  delay(100); // Short delay to allow the voltage to stabilize

  int rawValue = analogRead(BATTERY_PIN); // Read the raw value from the analog pin
  float voltage = rawValue * (MAX_VOLTAGE / 1023.0); // Convert the raw value to voltage

  digitalWrite(ENABLE_PIN, LOW); // Disable battery voltage measurement

  Serial.print("Battery Voltage: ");
  Serial.print(voltage);
  Serial.println("V");

  if (voltage > 4.0) {
    Serial.println("Battery Health: Excellent");
  } else if (voltage > 3.7) {
    Serial.println("Battery Health: Good");
  } else if (voltage > 3.4) {
    Serial.println("Battery Health: Fair");
  } else if (voltage > 3.0) {
    Serial.println("Battery Health: Poor");
  } else {
    Serial.println("Battery Health: Critical - Recharge immediately!");
  }

  delay(5000); // Wait for 5 seconds before the next reading
}
