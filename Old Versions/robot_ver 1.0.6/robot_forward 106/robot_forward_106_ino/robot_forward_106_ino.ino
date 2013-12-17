#include <MelodyUtils.h>
#include <pitches.h>
#include <Servo.h>
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
long duration, leftdistance, rightdistance, diagonalL, diagonalR, frontdistance, distance, leftside, rightside; // Duration used to calculate distance

Servo left; //left motor
Servo right; //right motor
Servo head;  // Head with mounted servo
void setup()
{
  left.attach(0); //Servos attached to pins 0,1 and 4
  right.attach(1);
  head.attach(4);
  pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 MelodyUtils mel(11); // Speaker pin
 mel.Glis(NOTE_C5, NOTE_C6, 1); //Startup tone
}
void loop() 
{    
    delay(500);  
    head.write(90);   //Head in center position
    scan();
    frontdistance = distance;
    if(frontdistance > 50 || frontdistance == 0)
    {moveForward();
    }
    else
    {
      moveStop();
      MelodyUtils mel(11);
      mel.Trem(NOTE_C6, 500, 20);
      head.write(124);  //Head in Diagonal Right position
      delay(500);
      scan();
      diagonalR = distance;
      head.write(158);   //Head in Right position
      delay(500);
      scan();
      rightdistance = distance;
      if(diagonalR > rightdistance)
      {
        rightside = diagonalR;
      }
      else(rightside = leftdistance);
      
      head.write(58);   //Head in Diagonnal Left position
      delay(500);
      scan();
      diagonalL = distance;
       head.write(25);   //Head in Left position
      delay(500);
      scan();
      leftdistance = distance;
       if(diagonalL > leftdistance)
      {
        leftside = diagonalL;
      }
      else(leftside = leftdistance);
      
      if(rightside < leftside)
      {
        moveBackward();
        delay(400);
        moveLeft();
        delay(450);
      }
      else if (leftside < rightside)
      {
        moveBackward();
        delay(400);
        moveRight();
        delay(450);
    }
    else
    {
      moveBackward();
      delay(400);
      moveRight();
      delay(500);
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

