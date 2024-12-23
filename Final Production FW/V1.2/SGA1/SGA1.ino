
const int ledPin = PIN_PB3;  
const int ledGPin = PIN_PA7;  

const int buttonPin = PIN_PA4;
const int buttonPin2 = PIN_PA5;
const int buttonPin3 = PIN_PB5;
const int buzzerPin = PIN_PC2;
const int relayPin = PIN_PC0;

char command; 
int active;
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
  


  if ((digitalRead(buttonPin) == LOW) && (digitalRead(buttonPin3) == LOW)) {
    Serial.println('1');
    digitalWrite(ledGPin, HIGH); 
    delay(100);    
  }else{
    digitalWrite(ledGPin, LOW); 
  }

  while (Serial.available() > 0) {
    command = Serial.read();  // Read the command sent by the master
    if ( (command == '3')  ) {
      active = 1;
      //delay(200); 
    }else{
      active = 0;
    }
  }

  if ((digitalRead(buttonPin2) == LOW) && (digitalRead(buttonPin3) == LOW)) {
    active = 0;
    delay(100);
  }

    if (active == 1) {
      Serial.println('1');
      digitalWrite(ledPin, HIGH);
      tone(buzzerPin,1047);
      delay(100);
    } else {
      digitalWrite(ledPin, LOW);
      //digitalWrite(buzzerPin, LOW);
      noTone(buzzerPin);
      digitalWrite(relayPin, LOW);
    }

}
