#include <Servo.h>
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
long duration, leftdistance, rightdistance, frontdistance, distance; // Duration used to calculate distance


Servo head;
int pos = 90;
void setup()
{
  //left.attach(0);
  //right.attach(1);
  head.attach(4);
  pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
}
void loop() 
{    
    delay(500);  
    head.write(58);
   
 }
   

void scan()
{
   digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
}
