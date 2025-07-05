#include <Servo.h>
#include <Arduino.h>
int a,b,r,q,count=0;
int x=2;
int y=2;
const int dirPin = 8;
const int stepPin = 5;
const int ms1Pin = 10;
const int ms2Pin = 11;
const int ms3Pin = 12;
const int enablePin = 3;

const int dir=13;
const int step=2;
const int ms1=4;
const int ms2=6;
const int ms3=7;

int DELAY=50;//y axis
int Delay=50;//x axis


void setup() {
Serial.begin(1000000); 
pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(ms1Pin, OUTPUT);
  pinMode(ms2Pin, OUTPUT);
  pinMode(ms3Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(step,OUTPUT);
  pinMode(dir,OUTPUT);
  pinMode(ms1,OUTPUT);
  pinMode(ms2,OUTPUT);
  pinMode(ms3,OUTPUT);


  // Set enable pin low to enable the driver
  digitalWrite(enablePin, LOW);

  // Set microstepping mode (e.g., 1/16 step)
  digitalWrite(ms1Pin, HIGH);
  digitalWrite(ms2Pin, HIGH);
  digitalWrite(ms3Pin, HIGH);
  digitalWrite(ms1, HIGH);
  digitalWrite(ms2, HIGH);
  digitalWrite(ms3, HIGH);

  }
void loop() {

  if (Serial.available() > 0) {
   


    String data = Serial.readStringUntil('\n'); // Read data until newline character
    int commaIndex = data.indexOf(','); // Find the index of the comma separating x and y coordinates
     
    if (commaIndex != -1) {
      String xCoord = data.substring(0, commaIndex); // Extract x coordinate substring
      String yCoord = data.substring(commaIndex + 1); // Extract y coordinate substring
      
       x = xCoord.toInt(); // Convert x coordinate to integer
       y = yCoord.toInt(); // Convert y coordinate to integer

       
      
      



  }


  
           count=0;


  }
if(count>10)
{
x=2;
y=2;
}



  
  if(x==0)
{
plus();
}
else if(x==1)
{
minus();
}

if(y==0)
Minus();

else if(y==1)
Plus();

count++;

}
void minus()
{
digitalWrite(dirPin, HIGH);
  
  // Rotate the motor 200 steps (one full revolution if 1.8° per step)
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(DELAY); // Adjust delay to control speed
    digitalWrite(stepPin, LOW);
    delayMicroseconds(DELAY); // Adjust delay to control speed
  

  
  
}

void plus()
{  

digitalWrite(dirPin, LOW);
  
  // Rotate the motor 200 steps (one full revolution if 1.8° per step)
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(DELAY); // Adjust delay to control speed
    digitalWrite(stepPin, LOW);
    delayMicroseconds(DELAY); // Adjust delay to control speed
  

  
}


void Plus()
{
  digitalWrite(dir,HIGH);


  digitalWrite(step,HIGH);
  delayMicroseconds(Delay);
  digitalWrite(step,LOW);
  delayMicroseconds(Delay);
  
    // Adjust delay to control speed


}


void Minus()
{
  digitalWrite(dir,LOW);


  digitalWrite(step,HIGH);
  delayMicroseconds(Delay);
  digitalWrite(step,LOW);
  delayMicroseconds(Delay);
  
  
}