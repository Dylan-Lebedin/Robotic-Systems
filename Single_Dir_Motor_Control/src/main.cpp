#include <Arduino.h>
#define motorpin A0 
void setup() {
  // pinMode(motorpin,OUTPUT);
}
 
void loop() {
  for(int i = 0;i<255;i= i+15)
  {
    analogWrite(motorpin,i);
    Serial.println(i);
    delay(100);
  }
  delay(100);
for(int i = 255;i>0;i= i-15)
  {
    analogWrite(motorpin,i);
    Serial.println(i);
    delay(100);
  }
}