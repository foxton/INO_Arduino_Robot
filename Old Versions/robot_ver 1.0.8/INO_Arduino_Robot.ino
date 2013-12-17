// INO ARDUINO ROBOT
// Version: 1.0.8
//Programmer: FoxtoN
#include <MelodyUtils.h>
#include <pitches.h>
#include <Servo.h>
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
long duration, leftdistance, rightdistance, diagonalLdistance, diagonalRdistance, frontdistance, distance; // Duration used to calculate distance

Servo left; //left motor
Servo right; //right motor
Servo head;  // Servo "head" with ultrasonic sensor

void setup()
{
  left.attach(0); //Servos attached to pins 0,1 and 4
  right.attach(1);
  head.attach(4);
  pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 MelodyUtils mel(11); // Speaker pin
 mel.Glis(NOTE_C6, NOTE_C7, 1); //Startup tone
 lookForward();
 frontdistance = scan();
}
void loop() 
{    
if((frontdistance > 60) || (frontdistance == 0))   //If no obstacle ahead, move forward
{
   moveForward();
   lookdiagonalL();
   diagonalLdistance = scan();
   checkdiagonalL();	//If approaching wall(side) turn slightly in opposite direction
   lookLeft();
   leftdistance = scan();
   checkLeft();          //If approaching wall(side) turn slightly in opposite direction
   lookForward();
   frontdistance = scan();
   if((frontdistance > 60) || (frontdistance == 0))   //If no obstacle ahead, move forward
   {
   moveForward();
   lookdiagonalR();
   diagonalRdistance = scan();
   checkdiagonalR();	//If approaching wall(side) turn slightly in opposite direction
   lookRight();
   rightdistance = scan();
   checkRight();        //If approaching wall(side) turn slightly in opposite direction
   }
   else  //When approaching wall (Front)  (Look left -> look forward -> ping
    {
  //MelodyUtils mel(11);
  //mel.Trem(NOTE_C7, 500, 20);
 moveStop();
 lookLeft();
 leftdistance = scan();
 lookRight();
 rightdistance = scan();
 lookForward();
 if ( leftdistance < rightdistance)
    {
 moveBackward();
 delay(600);
 moveRight();
 delay(325);
 frontdistance = scan();
     }
 else
 {
   moveBackward();
   delay(600);
   moveLeft();
   delay(365);
  frontdistance = scan();
 }
 

 }
   lookForward();
   frontdistance = scan();
 }
 else   //When approaching wall (Front) (look right -> look forward -> ping)
 {
  MelodyUtils mel(11);
  mel.Trem(NOTE_C7, 500, 20);
 moveStop();
 lookLeft();
 leftdistance = scan();
 lookRight();
 rightdistance = scan();
 lookForward();
 
if ( leftdistance < rightdistance)
 {
 moveBackward();
 delay(600);
 moveRight();
 delay(685);
 frontdistance = scan();
 }
 else
 {
   moveBackward();
   delay(600);
   moveLeft();
   delay(735);
  frontdistance = scan();
 }
 

 }
 

 }
  
void moveForward()                                    
{
  left.attach(0);
   right.attach(1);
  left.write(125);  //Left servo -> High value = forward
  right.write(12);  // Right servo -> Low value = forward
}  
void moveBackward()                                  
{
   left.attach(0);
 right.attach(1);
  left.write(20);    //Left servo -> Low value = backward
  right.write(140);  // Right servo -> High value = backward
  
}
void moveStop()
{
   left.detach();
   right.detach();
}
void stopLeft()
{
  left.detach();
}
void stopRight()
{
 right.detach();
}
void moveLeft()
{
  if(!right.attached())
{
  right.attach(1);
  left.attach(0);
} 
  right.write(16);
  left.write(20);
}
void moveRight()
{
 if(!left.attached())
{
  left.attach(0);
  right.attach(1);
} 
  left.write(136);
  right.write(140);
  
}
void lookForward()
{
	head.write(90);
	delay(500);
}
void lookdiagonalL()
{
	head.write(58);
	delay(500);
}
void lookLeft()
{
	head.write(25);
	delay(500); 
}
void lookdiagonalR()
{
	head.write(124);
	delay(500);
}
void lookRight()
{
	head.write(158);
	delay(500); 
}
void checkdiagonalL()
{
 if((diagonalLdistance < 40) && (diagonalLdistance != 0))  //If approaching wall(side) move in opposite direction
  {
   MelodyUtils mel(11);
   mel.Trem(NOTE_C7, 500, 20);
     stopRight();
     delay(10);
   }
   else
   {
     lookLeft();
     leftdistance = scan();
   }
}
void checkLeft()
{
 if((leftdistance < 40) && (leftdistance != 0))  //If approaching wall(side) move in opposite direction
  {
   MelodyUtils mel(11);
   mel.Trem(NOTE_C7, 500, 20);
     stopRight();
     delay(10);
   }
   else
   {
     lookForward();
     frontdistance = scan();
   }
}

void checkdiagonalR()
{
 if((diagonalRdistance < 40) && (diagonalRdistance != 0))  //If approaching wall(side) move in opposite direction
  {
   MelodyUtils mel(11);
   mel.Trem(NOTE_C7, 500, 20);
     stopLeft();
     delay(10);
   }
   else
   {
     lookRight();
     rightdistance = scan();
   }
}
void checkRight()
{
  if ((rightdistance < 40) && (rightdistance != 0))  //If approaching wall(side) move in opposite direction
   {
   MelodyUtils mel(11);
   mel.Trem(NOTE_C7, 500, 20);
   stopLeft();
   delay(10);
   }
   else
   {
     lookForward();
     frontdistance = scan();
   }
}

void checkFront()
{
  
}
long scan()   //Scan function that returns long
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
