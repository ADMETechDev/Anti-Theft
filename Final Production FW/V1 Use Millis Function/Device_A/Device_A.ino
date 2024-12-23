const int ledPin = PIN_PB3;  
const int ledGPin = PIN_PA7;  
const int buttonPin = PIN_PA4;
const int buttonPin2 = PIN_PA5;
const int buzzerPin = PIN_PC2;
const int relayPin = PIN_PC0;

int command, active;
unsigned long previousMillis = 0;
const long interval = 200;  // Interval for buzzer and LED

void setup() {
  Serial.swap(1);
  Serial.begin(1200);  // Initialize serial communication

  pinMode(buttonPin, OUTPUT);
  digitalWrite(buttonPin, HIGH);
  delay(100);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (Serial.available() > 0) {
    command = Serial.read();  // Read the command sent by the master
    if (command == '3') {
      digitalWrite(ledPin, HIGH);  // Turn the LED on
      tone(buzzerPin, 1047);

      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        digitalWrite(relayPin, HIGH);  // Activate relay
      }
    } else {
      digitalWrite(ledPin, LOW);
      noTone(buzzerPin);
      digitalWrite(relayPin, LOW);
    }
  }

  if (digitalRead(buttonPin) == LOW) {
    active = 1;
    digitalWrite(ledGPin, HIGH);
    delay(30);  // Debounce delay
    digitalWrite(ledGPin, LOW);
  }

  if (digitalRead(buttonPin2) == LOW) {
    active = 0;
    delay(30);  // Debounce delay
  }

  if (active == 1) {
    Serial.println('1');
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1047);

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(ledPin, LOW);
    }
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    digitalWrite(relayPin, LOW);
  }
}
