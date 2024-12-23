
const int ledPin = PIN_PB3;  
const int ledGPin = PIN_PA7;  

const int buttonPin = PIN_PA4;
const int buttonPin2 = PIN_PA5;
const int buttonPin3 = PIN_PB5;
const int buzzerPin = PIN_PC2;
const int relayPin = PIN_PC0;

int command, active;
void setup() {
  Serial.swap(1);
  Serial.begin(1200);  // Initialize serial communication

  pinMode(buttonPin,OUTPUT);
  digitalWrite(buttonPin,HIGH);
  delay(100);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  /*
  if (Serial.available() > 0) {
    command = Serial.read();  // Read the command sent by the master
    if (command == '3') {
      digitalWrite(ledPin, HIGH);  // Turn the LED on
      //digitalWrite(buzzerPin, HIGH);
      tone(buzzerPin,1047);
      delay(200);
      digitalWrite(relayPin, HIGH); 
    }else{
      digitalWrite(ledPin, LOW);
     //digitalWrite(buzzerPin, LOW); 
     noTone(buzzerPin);
     digitalWrite(relayPin, LOW);
    }
  }
  */

  if ((digitalRead(buttonPin) == LOW) && (digitalRead(buttonPin3) == LOW)) {
    active = 1;
    digitalWrite(ledGPin, HIGH); 
    delay(30);
    digitalWrite(ledGPin, LOW); 
  }
  if ((digitalRead(buttonPin2) == LOW) && (digitalRead(buttonPin3) == LOW)) {
    active = 0;
    delay(30);
  }

  if (active == 1) {
    Serial.println('1');
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin,1047);
    delay(200);
  } else {
    digitalWrite(ledPin, LOW);
    //digitalWrite(buzzerPin, LOW);
    noTone(buzzerPin);
    digitalWrite(relayPin, LOW);
  }
}
