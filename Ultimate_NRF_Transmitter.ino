#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

float calcmotval;
int motval;
int RYVal;

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

display.begin();

  display.clearDisplay(); // initial clearing of the display

 
  WelcomeWilliam(); //Welcomes me through OLED Panel.
  
  

 transmitter.begin();
 transmitter.openWritingPipe(address);  
 transmitter.setPALevel(RF24_PA_MAX);
 transmitter.stopListening();




digitalWrite(4, HIGH);
delay(1000);
digitalWrite(5, HIGH);
delay(500);
digitalWrite(4, LOW);
digitalWrite(5, LOW);


ValuestoOLED();// Displays Joystick Values to OLED Panel
 

}

void loop() {

while(transmitter.isChipConnected () == true){
  
 sensvals[0] = analogRead(A0);
  sensvals[1] = analogRead(A1);
   sensvals[2] = analogRead(A2);
    sensvals[3] = analogRead(A3);
     sensvals[4] = analogRead(A6);
      sensvals[5] = analogRead(A7);
       
  
 
  Serial.println(calcmotval);
  Serial.println("It is Connected!");
delay(50);
  
transmitter.write(&calcmotval,sizeof(calcmotval));


  
}
  

}

void ValuestoOLED(){

display.clearDisplay();
 display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(motval);
  display.print(" ");
  display.print(RYVal);
  display.setTextSize(1.5);
  display.println("");
  display.println("");
  display.println("");
  display.println("LY           RX");
  display.display();

}


void WelcomeWilliam(){
  
 display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("WELCOME");
  display.display();

  delay(2000);

display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("William");
  display.display();

  delay(3000);
  display.clearDisplay();

}

