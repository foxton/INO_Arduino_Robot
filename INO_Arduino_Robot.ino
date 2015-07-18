// INO ARDUINO ROBOT
// Version: 1.1.0
//Programmer: FoxtoN

/*Include Libraries*/
#include <Servo.h>

/*Declarations*/
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
long duration, leftdistance, rightdistance, diagonalLdistance, diagonalRdistance, frontdistance, distance; // Duration used to calculate distance
Servo left; //left motor
Servo right; //right motor
Servo head; // Servo "head" with ultrasonic sensor
long start = 0;
int switchPin = 3;
volatile int switchState = 0;
int speakerPin = 11;



/*Setup Code*/

void setup()
{
/*Attach servo and assign inputs/outputs*/
 head.attach(4);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(switchPin, INPUT);
 pinMode(speakerPin, OUTPUT);
 pinMode(13,OUTPUT);

 /* Attach the interrupt */
 attachInterrupt(1,react,RISING);

 /* Put servo in start position */
 lookForward();

	/*Serial for debugging	*/
	//Serial.begin(9600);
}

/* LOOP	*/

void loop()
{
	lookForward();
	lookLeft();
	lookRight();
}

 

 

 /*Functions*/

/*Interrupt function called when front switch changes state*/

void react()
{
	digitalWrite(13,HIGH);
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
        delay(20);
}


void lookLeft()
{
  for(int i = 93; i>=26; i-=1)
  {
        head.write(i);
	//	scan(i);
        delay(20);
  }
   for(int i = 25; i<=92; i+=1)
  {
        head.write(i);
		//scan(i);
        delay(20);
  }

}


void lookRight()
{
  for(int i = 93; i <= 157; i+=1)
  {
	head.write(i);
	delay(20);
   }
  for(int i = 158; i>=94; i-=1)
  {
	head.write(i);
	delay(20);
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

long scan(int servonumber) //Scan function that returns long
{
   digitalWrite(trigPin, LOW);
 delayMicroseconds(2);

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 return distance;
}



