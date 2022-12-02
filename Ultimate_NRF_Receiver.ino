#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Wire.h>
#include <Servo.h>

float calcmotval;
int motval;
int RYVal;

RF24 receiver(8,7);// CE and CS Pins

const byte address[6] = {"24"};

float sensvals;

Servo ailerons;
Servo rutter;
Servo elevator;
Servo frontprop;


int val;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);


 receiver.begin();
   receiver.openReadingPipe(0, address);  
     receiver.setPALevel(RF24_PA_MAX);
       receiver.startListening();

 ailerons.attach(3);
   rutter.attach(5);
     frontprop.attach(6);
       elevator.attach(9);
  
  





 

}

void loop() {

while(receiver.isChipConnected () == true){

 float sensvals [5];
 
  
delay(50);
  
receiver.read(&sensvals,sizeof(sensvals));
Serial.println(sensvals[1]);

ailerons.write(sensvals[1]);
  rutter.write(sensvals[2]);
    frontprop.write(sensvals[3]);
        elevator.write(sensvals[4]);

  
}
  

}
