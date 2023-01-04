#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Wire.h>
#include <Servo.h>

float calcmotval;
int motval;
int RYVal;

RF24 receiver(8,10);// CE and CS Pins

const byte address[6] = {"24"};

float sensvals [5];

Servo servo1;


int val;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);


 receiver.begin();
 receiver.openReadingPipe(0, address);  
 receiver.setPALevel(RF24_PA_MIN);
 receiver.setDataRate(RF24_250KBPS);
 receiver.startListening();

 servo1.attach(3);





 

}

void loop() {

while(receiver.isChipConnected () == true){

 
 
  
delay(50);
  
receiver.read(&sensvals,sizeof(sensvals));
Serial.println(sensvals[1]);

servo1.write(sensvals[1]);


  
}
  

}
