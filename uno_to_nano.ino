/*
   Recieves signal from uno to open or close the claw.
*/

#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//intialize variables for the servo mottor that controls the claw
int servoPin = 9;
int startPos = 0;
int pos;
bool isOpen = false;

//creates servo object
Servo myservo;

//creates radio object, CE and CSN
RF24 radio(7, 8);

//pipe address for nRF24(2.4 gHz), used for communicatioin
const byte address[6] = "00001";

void setup() {
  myservo.attach(servoPin);
  myservo.write(startPos);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text[32], sizeof(text));
    if (text == "1") {
      if (isOpen == false) {
        openClaw();
      } else {
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
