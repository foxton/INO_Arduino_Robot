#include <Servo.h>
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
long duration, leftdistance, rightdistance, frontdistance, distance; // Duration used to calculate distance

Servo left;
Servo right;
Servo servo;
void setup()
{
  left.attach(0);
  right.attach(1);
  servo.attach(4);
  pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
}
void loop() 
{    
    delay(500);  
    servo.write(90);
    scan();
    frontdistance = distance;
    if(frontdistance > 50 || frontdistance == 0)
    {moveForward();
    }
    else
    {
      moveStop();
      servo.write(158);
      delay(500);
      scan();
      rightdistance = distance;
      servo.write(25);
      delay(500);
      scan();
      leftdistance = distance;
      if(rightdistance < leftdistance)
      {
        moveLeft();
        delay(1000);
      }
      else if (leftdistance < rightdistance)
      {
        moveRight();
        delay(1000);
    }
    else
    {
      moveBackward();
      delay(200);
      moveRight();
      delay(200);
    }
    }

}
void moveForward()                                    
{
  left.attach(0);
   right.attach(1);
  left.write(140);
  right.write(20);
}  
void moveBackward()                                  
{
   left.attach(0);
  right.attach(1);
  left.write(20);
  right.write(140);
  
}
void moveStop()
{
   left.detach();
   right.detach();
}
void moveLeft()
{
  right.attach(1);
  right.write(20);
}
void moveRight()
{
  left.attach(0);
  left.write(140);
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
