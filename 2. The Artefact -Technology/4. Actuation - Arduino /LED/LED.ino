//Led and Push Button Interfacing
const int button = 8;   //led connected here   
const int led =  13; //push button connected here   
int buttonStatus = 0;  
const int button2 = 3;   //led connected here   
const int led2 =  6; //push button connected here   
int buttonStatus2 = 0;  


void setup() {
  pinMode(led,HIGH);
  pinMode(button,LOW);
  pinMode(led2,HIGH);
  pinMode(button2,LOW);
}

void loop() {
  buttonStatus = digitalRead(button);
  if (buttonStatus == HIGH) {    
    digitalWrite(led, HIGH);
  }
  else {   
    digitalWrite(led, LOW);
  }
  
  buttonStatus2 = digitalRead(button2);
  if (buttonStatus2 == HIGH) {    
    digitalWrite(led2, HIGH);
  }
  else {   
    digitalWrite(led2, LOW);
  }
}
