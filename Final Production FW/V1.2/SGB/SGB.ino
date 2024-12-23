
const int ledPin = PIN_PB2;  // LED connected to digital pin 4
const int buzzerPin = PIN_PB3;
const int relayPin = PIN_PC1;

int command;
int accum;

void setup() {
  Serial.swap(1);
  Serial.begin(1200);  // Initialize software serial communication
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); 
}

void loop() {
  while (Serial.available() > 0) {
    command = Serial.read();  // Read the command sent by the master
    if (command == '1') {
      digitalWrite(ledPin, HIGH);
      digitalWrite(relayPin, LOW);
      accum++;
      Serial.println('3');
      //digitalWrite(buzzerPin, HIGH);
      tone(buzzerPin,1047,100);
      delay(100);
      tone(buzzerPin,1760,200);
      delay(100);
       
      
      //delay(500);
    

    }else {
      accum--;
      if(accum > 10){
        accum = 10;
      }
      delay(200);
    }
  }

  if(accum<1){
    digitalWrite(ledPin, LOW);
    //digitalWrite(buzzerPin, LOW);
    noTone(buzzerPin);
    digitalWrite(relayPin, HIGH); 
  }
}
