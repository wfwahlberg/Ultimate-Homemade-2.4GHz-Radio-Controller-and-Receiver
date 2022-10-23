#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

float calcmotval;

#define SSD1306_128_32

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


RF24 transmitter(8,10);// CE and CS Pins

const byte address[6] = {"24"};

int sensvals[10];


int val;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(A0, INPUT);// Right Joystick X Val
  pinMode(A1, INPUT);// Right Joystick Y Val
  pinMode(A2, INPUT);// Right Potentiometer
  pinMode(A3, INPUT);// Left Potentiometer
  pinMode(A6, INPUT);// Left Joystick X Val
  pinMode(A7, INPUT);// Left Joystick Y Val
  pinMode(3, OUTPUT); // RED RGB
  pinMode(4, OUTPUT); // GREEN RGB
  pinMode(5, OUTPUT);// BLUE RGB
  
  
  

 transmitter.begin();
 transmitter.openWritingPipe(address);  
 transmitter.setPALevel(RF24_PA_MAX);
 transmitter.stopListening();

}

void loop() {
  // put your main code here, to run repeatedly:


 
  


while(transmitter.isChipConnected () == true){
  
 int motval = analogRead(A7);
 float calcmotval = (motval/1023.)*180.;
  Serial.println(calcmotval);
  Serial.println("It is Connected!");
delay(50);
  
transmitter.write(&calcmotval,sizeof(calcmotval));


  
}
  

}
