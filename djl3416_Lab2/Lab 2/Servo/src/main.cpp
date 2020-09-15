// To enable word wrap -> Alt + Z 

/*
  This program will help you understand how to control servos. Read through the program and comment with enough detail explaining everything that is going on. Please comment line by line with a quick summary before each function. 

  Try this code to see what it does.
*/

#include <Arduino.h>
#include <Servo.h> 

#define Servo_Pin 1

Servo s; // <- is this a variable?
int pos;

void setup() 
{ 
  pinMode(Servo_Pin, OUTPUT);
  s.attach(Servo_Pin);
  s.write(90);  // Set servo to mid-point
  delay(500);
} 
/*
  Next write code that makes the Servo oscillate from 0 - 2pi/3 radians every 5 seconds.
*/ 

void loop() {
  for (pos = 0; pos <= 120; pos += 1) { // goes from 0 degrees to 120 degrees
    // in steps of 1 degree
    s.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20.83);                       // waits 20.83ms for the servo to reach the position
  }
  for (pos = 120; pos >= 0; pos -= 1) { // goes from 120 degrees to 0 degrees
    s.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20.83);                       // waits 20.83ms for the servo to reach the position
  }
} 
