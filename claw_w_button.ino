#include <Servo.h>

//Setup servo motor and push button
Servo myservo;
int button = 13;

//intitalize position, isOpen, and buttonPressed 
int pos = 0;
bool isOpen = false;
bool buttonPressed = false;

void setup() {
  //intialize the servo motor and push button for use
  myservo.attach(9);
  pinMode(button, INPUT);

  //sets servo to closed position on startup 
  myservo.write(pos);

  Serial.begin(9600);
}

void loop() {
  //detect button push
  if (digitalRead(button) == HIGH) {
    delay(150);
    buttonPressed = true;
  }

  //determines if claw needs to be closed or open depending on current state 
  while (buttonPressed == true) {
    if (isOpen == false) {
      openClaw();
    } else {
      closeClaw();
    }
    buttonPressed = false;
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
