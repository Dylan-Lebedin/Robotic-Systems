#include "QuadDecoder.h"
//#include <ADC.h>
#include <Arduino.h>
#include <math.h>

 
#define MotorA_nD2 14 // Enable Pin
#define MotorA_DIR 15 // Direction Pin
#define MotorA_PWM 13 // PWM Pin
#define MotorA_nSF 16 // Fault Pin
#define MotorA_FB 17 // Current Feedback Pin
 
#define TICKS_PER_REV 2256 // Number of ticks per wheel revolution
#define PERIOD 10000     // How fast velocity is calculated in microseconds
 
QuadDecoder<1> Enc1; //New Quadrature Encoder Object
IntervalTimer velTimer;
//ADC * adc = new ADC(); // adc object
//gear ratio of 47 and count per minute is 48
//(6*10^6)/(10^3*48*47)
const double rpmConvert = 2.66; // Determine this value
 
// Variables to be used in the timer interrupt
volatile int oldCntA = 0; // used to store the count the last time you calculated
volatile int newCntA = 0; //  new value to use in calculating difference
volatile int diffA = 0;   // difference between newCntA and oldCntA
volatile int vel = 0;
 
void calcVel(void) // --- Finish this function ---
{
    // This function automatically runs -> 
    // Use the getCount function from the QuadDecoder class to determine the change in counts
    // remeber to update oldCntA
    oldCntA = newCntA;
    newCntA = Enc1.getCount();
    diffA = (newCntA - oldCntA);
    vel = diffA * rpmConvert;
        
}
 
void setup()
{
    // Quadtrature decoder setup
    Enc1.begin(TICKS_PER_REV);
 
    // Pin Assignments
    pinMode(MotorA_nD2, OUTPUT); // Enable Pin
    pinMode(MotorA_DIR, OUTPUT); // Direction Pin
    pinMode(MotorA_PWM, OUTPUT); // PWM Pin
    pinMode(MotorA_nSF, INPUT);  // Fault Pin
    pinMode(MotorA_FB, INPUT);   // Current Feedback Pin
 
    // enable motor controller
    digitalWrite(MotorA_nD2, HIGH);
 
    // Start Serial Monitor
    Serial.begin(9600);
    delay(100);
 
    // Timer for velocity
    velTimer.begin(calcVel, PERIOD);
 
    // Set ADC
    //adc->setAveraging(4);                                     // set number of averages
    //adc->setResolution(12);                                   // set bits of resolution
    //adc->setConversionSpeed(ADC_CONVERSION_SPEED::LOW_SPEED); // change the conversion speed
    //adc->setSamplingSpeed(ADC_SAMPLING_SPEED::LOW_SPEED);     // change the sampling speed
    //adc->startContinuous(MotorA_FB, ADC_0);
}
 
void loop()
{
    // Implement code here that makes the Motor move forward and backwards and stops. While doing this, make three graphs.
    // 1) Velocity vs. Time
    // 2) Current vs. Time
    // 3) Velocity vs. Current
    // NOTE: Velocity must be in RPM.
    delay(5000);
    digitalWrite(MotorA_nD2, HIGH);
    Serial.println("FORWARD");
    for (int i = 0; i <= 255; i+= 5) {
      analogWrite(MotorA_PWM, i);
      digitalWrite(MotorA_DIR, LOW);
      int current_forward = analogRead(MotorA_FB);
      Serial.println(current_forward);
      Serial.println(diffA);
      Serial.println(micros());
      delay(100);
    }
    Serial.println("REVERSE");
    for(int i = 255; i >= 0; i-= 5) {
      analogWrite(MotorA_PWM, i);
      digitalWrite(MotorA_DIR, HIGH);
      int current_reverse = analogRead(MotorA_FB);
      Serial.println(current_reverse);
      Serial.println(diffA);
      Serial.println(micros());
      delay(100);
    }
    Serial.println("STOP");
    for(int i = 255; i >= 0; i-= 5) {
      analogWrite(MotorA_PWM, i);
      digitalWrite(MotorA_nD2, LOW);
      int current_stop = analogRead(MotorA_FB);
      Serial.println(current_stop);
      Serial.println(diffA);
      Serial.println(micros());
      delay(100);
    }
    
    delay(100000);
 
}

