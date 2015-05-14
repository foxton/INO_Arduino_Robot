// INO ARDUINO ROBOT
// Version: 1.0.9
//Programmer: FoxtoN

#include <Servo.h>
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
long duration, leftdistance, rightdistance, diagonalLdistance, diagonalRdistance, frontdistance, distance; // Duration used to calculate distance

Servo left; //left motor
Servo right; //right motor
Servo head; // Servo "head" with ultrasonic sensor
int switchPin = 2;
int switchState;
int speakerPin = 11;

void setup()
{
 
  head.attach(4);
  pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(switchPin, INPUT);
 pinMode(speakerPin, OUTPUT);
 lookForward();
 frontdistance = scan();
readSwitch();
//Serial.begin(9600); //For debugging
}
void loop()
{

if(switchState == HIGH)
{
 moveBackward();
 delay(400);
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
 readSwitch();

     }
 else
 {
   moveBackward();
   delay(600);
   moveLeft();
   delay(365);
  frontdistance = scan();
  readSwitch();
}
}
else
{

if((frontdistance > 60) || (frontdistance == 0 )) //If no obstacle ahead, move forward
{
	readSwitch();
   moveForward();
   lookdiagonalL();
   diagonalLdistance = scan();
   checkdiagonalL();        //If approaching wall(side) turn slightly in opposite direction
   readSwitch();
   lookLeft();
   leftdistance = scan();
   checkLeft(); //If approaching wall(side) turn slightly in opposite direction
   readSwitch();
   lookForward();
   frontdistance = scan();
   readSwitch();

   if(switchState == HIGH)  //
{
 moveBackward();
 delay(400);
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
 readSwitch();

     }
 else
 {
   moveBackward();
   delay(600);
   moveLeft();
   delay(365);
  frontdistance = scan();
  readSwitch();
}
}
else
{                     

   if((frontdistance > 60) || (frontdistance == 0)) //If no obstacle ahead, move forward
   {
   readSwitch();
   moveForward();
   lookdiagonalR();
   diagonalRdistance = scan();
   checkdiagonalR();        //If approaching wall(side) turn slightly in opposite direction
   readSwitch();
   lookRight();
   rightdistance = scan();
   checkRight(); //If approaching wall(side) turn slightly in opposite direction
   readSwitch();
   }
   else //When approaching wall (Front) (Look left -> look forward -> ping
    {

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
  readSwitch();
 }
 

 }
   lookForward();
   frontdistance = scan();
 }
}
 else //When approaching wall (Front) (look right -> look forward -> ping)
 {

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
 readSwitch();
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
 }
 

 




void moveForward()
{
  left.attach(0);
   right.attach(1);
  left.write(125); //Left servo -> High value = forward
  right.write(12); // Right servo -> Low value = forward
}

void moveforwardSlow()
{
 left.attach(0);
 right.attach(1);
 left.write(125); //Left servo -> High value = forward
 right.write(12); // Right servo -> Low value = forward
}

void moveBackward()
{
   left.attach(0);
 right.attach(1);
  left.write(20); //Left servo -> Low value = backward
  right.write(140); // Right servo -> High value = backward
  
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
	 head.write(93);
        delay(400);
}

void lookdiagonalL()
{
        head.write(58);
        delay(400);
}

void lookLeft()
{
        head.write(25);
        delay(400);
}

void lookdiagonalR()
{
        head.write(124);
        delay(400);
}

void lookRight()
{
        head.write(158);
        delay(400);
}

void checkdiagonalL()
{
 if((diagonalLdistance < 40) && (diagonalLdistance != 0)) //If approaching wall(side) move in opposite direction
  {
     stopRight();
     delay(20);
   }
   else
   {
     lookLeft();
     leftdistance = scan();
   }
}

void checkLeft()
{
 if((leftdistance < 40) && (leftdistance != 0)) //If approaching wall(side) move in opposite direction
  {

     stopRight();
     delay(20);
   }
   else
   {
     lookForward();
     frontdistance = scan();
   }
}

void checkdiagonalR()
{
 if((diagonalRdistance < 40) && (diagonalRdistance != 0)) //If approaching wall(side) move in opposite direction
  {

     stopLeft();
     delay(20);
   }
   else
   {
     lookRight();
     rightdistance = scan();
   }
}

void checkRight()
{
  if ((rightdistance < 40) && (rightdistance != 0)) //If approaching wall(side) move in opposite direction
   {
   stopLeft();
   delay(20);
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

void readSwitch()
{
switchState = digitalRead(switchPin);
delay(10);
}

long scan() //Scan function that returns long
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



