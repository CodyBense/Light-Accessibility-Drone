/*
   This code interfaces the uno to Matlab. Depending one the classifcation of the signal from the OpenBCI head band, the uno will either send a signal to the nano
   to open/close the claw or send a voltage to the controller to move the drone.
*/

//website used for 2.4 https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/

#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//creates radio object, CE and CSN
RF24 radio(7, 8);

//pipe address for nRF24(2.4 gHz), used for communicatioin
const byte address[6] = "00001";

//variables for HC-05(bluetooth)
int TxD;
int RxD;
int data;

//creates bluetooth object
SoftwareSerial bluetooth(TxD, RxD);

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  bluetooth.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (bluetooth.available() > 0) {
    data = bluetooth.read();
    if (data == '1') {
      sendClaw();
    } else if (data == '2') {
      raiseDrone();
    } else if (data == '3') {
      lowerDrone();
    }
  }

}

//sends the value of 1 to the other arduino
void sendClaw() {
  const char text[] = "1";
  radio.write(&text, sizeof(text));
  delay(1000);
}

//sends ___ volts to controller to raise drone
void raiseDrone() {

}

//sends ___ volts to controller to lower drone
void lowerDrone() {

}
