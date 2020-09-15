#include <Arduino.h>
#include <Wire.h>
#include "Pixy2SPI_SS.h"
#include "Pixy2CCC.h"
#include "QuadDecoder.h"
#include <Servo.h>

// defining the ultrasonic sensors
#define trigPinFront  18
#define echoPinFront 17
//#define trigPinSide 20
//#define echoPinSide 16

//define the reflectance sensors
//#define IRReflLeft A7
#define IRReflMid A8
//#define IRReflRight A9

//define the left motor
#define MotorLeft_DIR 15 // Direction Pin
#define MotorLeft_PWM 19 // PWM Pin
//#define MotorLeft_FB 19 // Current Feedback Pin

#define Motor_nD2 14 // Enable Pin
#define Motor_nSF 9 // Fault Pin

//define the right motor
#define MotorRight_DIR 7 // Direction Pin
#define MotorRight_PWM 3 // PWM Pin
//#define MotorRight_FB 4 // Current Feedback Pin

#define Rev_Servo 20
#define Trigger_servo 21
#define Trig_servo_2 22

#define TICKS_PER_REV 2256 //number of tickers per wheel revolution
#define PERIOD 10000 //how fast velocity is calculated in microseconds

Pixy2SPI_SS pixy;

int threshold_middle = 960;
int threshold_left = 970;
int threshold_right = 970; 

int Xtarget = 0;
int Ytarget = 0;
int pos;

Servo trig;
Servo left_trig;
Servo rev;

double duration_front, inches_front, duration_side, inches_side;

void DrivetoTarget();
void SearchForTarget();
void ExecuteTarget();

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  Serial.println("Setup Begin");
  //setup for ultrasonic sensors
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);
  //pinMode(trigPinSide, OUTPUT);
  //pinMode(echoPinSide, INPUT);

  //setup for reflectance sensors

  //pinMode(IRReflLeft, INPUT);
  pinMode(IRReflMid, INPUT);
  //pinMode(IRReflRight, INPUT);

  // Quadtrature decoder setup
  //Enc1.begin(TICKS_PER_REV);
  //Enc2.begin(TICKS_PER_REV);
 
  // Pin Assignments
  pinMode(Motor_nD2, OUTPUT); // Enable Pin
  pinMode(MotorLeft_DIR, OUTPUT); // Direction Pin
  pinMode(MotorLeft_PWM, OUTPUT); // PWM Pin
  pinMode(Motor_nSF, INPUT);  // Fault Pin
  //pinMode(MotorLeft_FB, INPUT);   // Current Feedback Pin

  pinMode(MotorRight_DIR, OUTPUT); // Direction Pin
  pinMode(MotorRight_PWM, OUTPUT); // PWM Pin
  //pinMode(MotorRight_FB, INPUT);   // Current Feedback Pin
 
  // enable motor controller
  digitalWrite(Motor_nD2, HIGH);

  pinMode(Rev_Servo, OUTPUT);
  pinMode(Trigger_servo, OUTPUT);
  pinMode(Trig_servo_2, OUTPUT);
  rev.attach(Rev_Servo);
  trig.attach(Trigger_servo);
  left_trig.attach(Trig_servo_2);
  rev.write(0);
  trig.write(0);
  left_trig.write(90);
  delay(500);

  pixy.init();
  Serial.begin(115200);
 
    // Start Serial Monitor
  //Serial.begin(9600);
  delay(100);
 
  // Timer for velocity
  //velTimer.begin(calcVel, PERIOD);
  Serial.println("Setup Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  // read the values of the reflectance sensors
  //int raw_value_left = analogRead(IRReflLeft);
  int raw_value_middle = analogRead(IRReflMid);
  //int raw_value_right = analogRead(IRReflRight);
  int motor_right_white = 100; //100
  int motor_left_white = 60; //60

  int motor_left_black = 120; //120
  int motor_right_black = 90; //90
  
  digitalWrite(trigPinFront, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFront, LOW);
   
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  //pinMode(echoPinFront, INPUT);
  duration_front = pulseIn(echoPinFront, HIGH);
 
  // Convert the time into a distance     
  inches_front = 0.0066*duration_front+0.1338;
  digitalWrite(MotorLeft_DIR, 200);
  analogWrite(MotorLeft_PWM, HIGH);
  digitalWrite(MotorRight_DIR, 200);
  analogWrite(MotorRight_PWM,HIGH);
  SearchForTarget();
  //DrivetoTarget();
  //ExecuteTarget();
  /*
  if ((inches_front < 5) && (inches_front > 2)) {
  //turn left
  Serial.println("IN OBSTACLE AVOIDANCE");
  Serial.println(inches_front);
  //turn 90 right  
  digitalWrite(MotorLeft_DIR, HIGH);
  analogWrite(MotorLeft_PWM, 0);
  digitalWrite(MotorRight_DIR, HIGH);
  analogWrite(MotorRight_PWM, 90);
  delay(1515);

  //go forward
  digitalWrite(MotorLeft_DIR, HIGH);
  analogWrite(MotorLeft_PWM, 90);
  digitalWrite(MotorRight_DIR, HIGH);
  analogWrite(MotorRight_PWM, 90);
  delay(1750); 

  //turn left
  digitalWrite(MotorLeft_DIR, HIGH);
  analogWrite(MotorLeft_PWM, 150);
  digitalWrite(MotorRight_DIR, HIGH);
  analogWrite(MotorRight_PWM, 95);
  delay(4450);

  digitalWrite(MotorLeft_DIR, HIGH);
  analogWrite(MotorLeft_PWM, 90);
  digitalWrite(MotorRight_DIR, HIGH);
  analogWrite(MotorRight_PWM, 90);
  delay(2000);
  /*
  while(raw_value_middle < 980) {
  Serial.println("in while");
  digitalWrite(MotorLeft_DIR, HIGH);
  analogWrite(MotorLeft_PWM, 90);
  digitalWrite(MotorRight_DIR, HIGH);
  analogWrite(MotorRight_PWM, 90);
  }
  */
  /*
  }
  
  else if (raw_value_middle > 990) {
    Serial.println("Seeing black");
    Serial.println(raw_value_middle);
    digitalWrite(MotorLeft_DIR, LOW);
    analogWrite(MotorLeft_PWM, motor_right_black);

    digitalWrite(MotorRight_DIR, HIGH);
    analogWrite(MotorRight_PWM, motor_left_black);
    delay(10);
  }

  else {
  Serial.println("Seeing white");
   Serial.println(raw_value_middle);
  digitalWrite(MotorLeft_DIR, HIGH);
    analogWrite(MotorLeft_PWM, motor_right_white);

  digitalWrite(MotorRight_DIR, LOW);
  analogWrite(MotorRight_PWM, motor_left_white);
  delay(10);
  }
*/
  
}

void DrivetoTarget() {
  digitalWrite(MotorLeft_DIR, 0);
  analogWrite(MotorLeft_PWM, HIGH);
  digitalWrite(MotorRight_DIR, 0);
  analogWrite(MotorRight_PWM,HIGH);
  delay(100);
  
  Serial.println("In Drive");
  digitalWrite(MotorLeft_DIR, 120);
  analogWrite(MotorLeft_PWM, HIGH);
  digitalWrite(MotorRight_DIR, 120);
  analogWrite(MotorRight_PWM,HIGH);

  digitalWrite(trigPinFront, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPinFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFront, LOW);
   
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  //pinMode(echoPinFront, INPUT);
  duration_front = pulseIn(echoPinFront, HIGH);
 
  // Convert the time into a distance     
  inches_front = 0.0066*duration_front+0.1338;
  Serial.println("Distance");
  Serial.println(inches_front);

  if ((inches_front < 30) && (inches_front > 24)) {
      ExecuteTarget();
  }
}

void SearchForTarget(){
  Serial.println("in searching function");
  pixy.changeProg("color_connected_components");
  pixy.ccc.getBlocks();
  
  digitalWrite(MotorLeft_DIR, 140);
  analogWrite(MotorLeft_PWM, HIGH);
  digitalWrite(MotorRight_DIR, 140);
  analogWrite(MotorRight_PWM,LOW);
  
    if(pixy.ccc.numBlocks) {
    Serial.println("Detected");
    //Serial.print(pixy.ccc.numBlocks);
    pixy.ccc.blocks[0].print();
    Xtarget = pixy.ccc.blocks[0].m_x; //center is 181
    Ytarget = pixy.ccc.blocks[0].m_y;  //y is 80

    //Serial.println("X");
    //Serial.println("Y");
    //Serial.println(Xtarget);
    //Serial.println(Ytarget);
    if ((160 < Xtarget) && (Xtarget < 200 ) && (60 < Ytarget) && (Ytarget < 100)) {
      Serial.println("In search");
      DrivetoTarget();
    }
  
  }


}

//144 is center
void ExecuteTarget () {
  Serial.println("IN EXECUTE");
    delay(4000);
    for (pos = 0; pos <= 180; pos += 5) {
      rev.write(pos);
      delay(10);
    }
                 // tell servo to go to position in variable 'pos'                       // waits 20.83ms for the servo to reach the position
   // goes from 120 degrees to 0 degrees
    //delay(3000);
    for (pos = 0; pos <= 180; pos += 5) {
        trig.write(pos);
        left_trig.write(180-pos);
        delay(10); 
    }             // tell servo to go to position in variable 'pos'                       // waits 20.83ms for the servo to reach the position
  // goes from 0 degrees to 120 degrees
    // in steps of 1 degree
    delay(4000);
    for (pos = 180; pos >= 0; pos -= 5) {
        left_trig.write(180-pos);
        trig.write(pos);
        delay(10); 
    }
    delay(1000);
    for (pos = 0; pos <= 180; pos += 5) {
      rev.write(pos);
      delay(10);
    }
                           // waits 20.83ms for the servo to reach the position
}


