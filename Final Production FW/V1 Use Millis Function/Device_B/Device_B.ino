const int ledPin = PIN_PB2;
const int buzzerPin = PIN_PB3;
const int relayPin = PIN_PC1;

int command;
unsigned int accum;
unsigned long previousMillis = 0;
const long interval = 200;

void setup() {
  Serial.swap(1);
  Serial.begin(1200);  // Initialize serial communication
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); 
}

void loop() {
  unsigned long currentMillis = millis();

  if (Serial.available() > 0) {
    command = Serial.read();  // Read the command sent by the master
    if (command == '1') {
      digitalWrite(ledPin, HIGH);
      digitalWrite(relayPin, LOW);
      accum++;

      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        tone(buzzerPin, 1047, 100);
        delay(100);
        tone(buzzerPin, 1760, 200);
      }
    }
  } else {
    accum--;
    if (accum > 50) {
      accum = 50;                   
    }
    delay(10);
  }

  if (accum < 1) {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    digitalWrite(relayPin, HIGH); 
  }
}
