/*
Pin connection
VL53L0X Pin  Arduino Pin
VCC         5V
GND         GND
SDA         A4 or SDA if available
SCL         A5 or SCL if available
GPIO1       leave it unconnected
XSHUT       D12 (digital 12 or pin 12)
*/

//#include <Wire.h>
//#include <VL53L0X.h>
#include <Arduino.h>
//#define LED_Pin 13

#define IRReflPin A7 //reflectance
//left
//VL53L0X sensor;

//String array[10];

//int count = 0;
void setup()
{
    //pinMode(LED_Pin, OUTPUT);
    pinMode(IRReflPin, INPUT);
    //pinMode(12, INPUT_PULLUP);
    //digitalWrite(12, HIGH);
    Serial.begin(9600);
    //Wire.begin();

    //sensor.init();
    //sensor.setTimeout(500);
    //sensor.startContinuous();
}

void loop()
{

    //int distance = sensor.readRangeContinuousMillimeters();
    int raw_value_0 = analogRead(IRReflPin); //reflectance
    //Serial.println(distance);
    //Serial.println('Test');
    //Serial.println(raw_value_0); 
    
        Serial.println(raw_value_0);
        delay(1000);
    
}
