/*
http://forum.arduino.cc/index.php/topic,43241.0.html

This program is an example of how to use SPI

*/

#include <Arduino.h>

// DO NOT DEFINE MASTER OR SLAVE.
// #define statements are preprocessor commands that are set during the build stage.
// Look at platformio.ini to see what is set when built

#ifdef MASTER
#include <SPI.h>

#define SS_PIN 9 // Please use pin 9 for your slave select pin

SPISettings settings(2000000, MSBFIRST, SPI_MODE1); 

void setup()
{
    SPI.begin();
}

void loop()
{
    while(Serial.available()) {
        int a = Serial.parseInt();
        int b = Serial.parseInt();

        SPI.beginTransaction(settings);
        digitalWrite(SS_PIN, LOW);
        SPI.transfer(a);
        Serial.println(a);
        SPI.transfer(b);
        Serial.println(b);
        digitalWrite(SS_PIN, HIGH);
        SPI.endTransaction();
        delay(100);
    }
    
}

#endif

#ifdef SLAVE
#include "SpiSlave.h"


void setup()
{
    Serial.begin(9600);
    SpiSlave.SPI_SlaveInit();
}

void loop()
{
    uint8_t RX_Data1;
    uint8_t RX_Data2;
    RX_Data1 = SpiSlave.SPI_SlaveReceive();
    delay(500);
    RX_Data2 = SpiSlave.SPI_SlaveReceive();
    //Serial.println(RX_Data1);
    //Serial.println(RX_Data2);
    Serial.println(RX_Data1 + RX_Data2);
    //Serial.println(RX_Data, HEX);
    //Serial.println("rx");
}
#endif

// In your report explain how the exchange of information is happening between the two teensys. ( We want to see how the master and slave communicate in bytes. )
// Change the program to make the Master send two numbers one after the other and make the slave calculate the sum and send it back.