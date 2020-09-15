// To enable word wrap -> Alt + Z 

/*
  This program will help you understand how to control servos. Read through the program and comment with enough detail explaining everything that is going on. Please comment line by line with a quick summary before each function. 

  Try this code to see what it does.
*/

#include <Arduino.h>

/*SHARP GP2Y0A21YK0F IR sensor with Arduino and SharpIR library example code. More info: https://www.makerguides.com */
// Include the library:
//#include <SharpIR.h>
// Define model and input pin:
#define IRPin A1
int count = 0;

void setup() {
    pinMode(IRPin, INPUT);

    // Turn on the serial monitor
    Serial.begin(9600);
}

void loop() {
    while (count < 500) {
        int raw_value = analogRead(IRPin);
        Serial.println(raw_value);
        double y = 30302*pow(raw_value, -1.371);
        Serial.println(y);
        count = count + 1;
        delay(500);
    }

    
}
