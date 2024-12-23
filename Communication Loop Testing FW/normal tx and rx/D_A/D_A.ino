const int ledPin = 6;      // LED connected to digital pin 6
const int buttonPin = 7;
const int buttonPin2 = 8;
const int buzzerPin = 9;


int command, active;
void setup() {
  Serial.begin(9600);  // Initialize software serial communication
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();  // Read the command sent by the master
    if (command == '3') {
      digitalWrite(ledPin, HIGH);  // Turn the LED on
      //digitalWrite(buzzerPin, HIGH);
      tone(buzzerPin,1047);
      delay(200); 
    }else{
      digitalWrite(ledPin, LOW);
     //digitalWrite(buzzerPin, LOW); 
     noTone(buzzerPin);
    }
   }
  if (digitalRead(buttonPin) == LOW) {
    active = 1;
    delay(30);
  }
  if (digitalRead(buttonPin2) == LOW) {
    active = 0;
    delay(30);
  }

  if (active == 1) {
    Serial.println('1');
    delay(100);
  } else {
    digitalWrite(ledPin, LOW);
    //digitalWrite(buzzerPin, LOW);
    noTone(buzzerPin);
  }
}
