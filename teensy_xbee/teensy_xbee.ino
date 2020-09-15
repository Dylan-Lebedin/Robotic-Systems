#include <Arduino.h>
#include "SoftwareSerial.h"
#include <Servo.h>

#define Servo_Pin 9

#define LED 13
#define Potentiometer A0
SoftwareSerial Xbee (0,1);
bool ledstate = 0;
Servo s;
int pos;


void setup()
{
    Xbee.begin(9600);
    Serial.begin(9600);
    delay(500);
    pinMode(LED, OUTPUT);
    pinMode(Servo_Pin, OUTPUT);
    s.attach(Servo_Pin);
    s.write(90);
    pinMode(Potentiometer, INPUT);
}

void loop()
{
    if(Xbee.available()) {
        
        int fuckthis = Xbee.read();
        if (fuckthis == 'a') {
            Serial.print("in function 1");
            if(ledstate == 1){
                digitalWrite(LED, LOW);
   
                ledstate = 0;
              }
             else {
                digitalWrite(LED, HIGH);
                ledstate = 1;
              }
              delay(50);
        }
        else if(fuckthis == 'd') {
            Serial.println("in function 2");
            delay(500);
            if (Xbee.available()){
                int angle = (int)Xbee.read();
                Serial.println(angle);
                s.write(0);
                delay(500);
                s.write(angle);
                delay(500);
            }
              delay(50);
          }
        else if(fuckthis == 'v') {
            for (int i = 0; i < 10; i++) {
              int raw_value = analogRead(Potentiometer);
              Serial.println(raw_value); // println() and print() do the same thing but print ln appends a new line character at the end of the string.
              delay(500); // Why is this needed?
            }
              delay(50);
          }
    }
    
}
