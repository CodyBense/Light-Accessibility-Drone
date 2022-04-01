#include <SoftwareSerial.h>
#include <Servo.h>

int TxD;
int RxD;
int data;
int pos = 0;
bool isOpen = false;

Servo myservo;
SoftwareSerial bluetooth(TxD, RxD);


void setup() {
  myservo.attach(9);

  myservo.write(pos);
  
  Serial.begin(9600); 
  bluetooth.begin(9600);
}

void loop(){
  
  if(bluetooth.available() > 0) {
    data = bluetooth.read();    
    Serial.print(data);       
    Serial.print("\n"); 

    if(data == '1') {         
      if(isOpen == true){
        openClaw();
      }else{
        closeClaw();
      }
    }
  }               
}

void closeClaw() {
  Serial.println("Closing");
  isOpen = false;
  for (pos = 90; pos >= 0; pos--) {
    myservo.write(pos);
    delay(10);
  }
}

void openClaw() {
  Serial.println("Opening");
  isOpen = true;
  for (pos = 0; pos <= 90; pos++) {
    myservo.write(pos);
    delay(10);
  }
}
