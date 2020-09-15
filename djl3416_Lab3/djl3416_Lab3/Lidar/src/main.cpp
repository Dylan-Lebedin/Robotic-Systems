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


#include <Wire.h>
#include <VL53L0X.h>
#define LED_Pin 13
VL53L0X sensor;

void setup()
{
  pinMode(LED_Pin, OUTPUT);
  pinMode(12,INPUT_PULLUP);
  digitalWrite(12,HIGH);
  Serial.begin(9600);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();
}

void loop()
{
  int distance =sensor.readRangeContinuousMillimeters();
  //int distance =sensor.startContinuous(100);
  
 //distance = distance;
  digitalWrite(LED_Pin, HIGH);
  delay(distance);
  digitalWrite(LED_Pin, LOW);
  delay(distance);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("mm");
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();
  delay(100);
}
  
