/*

This part of the lab is about analog signals and how to deal with them. Analog signals are important because every signal in the real world is an analog signal. To understand analog signals, we have to care more about the value of the signal to understand what the signal is telling us. For a microcontroller to analyze an analog signal, the signal needs to be converted to a digital signal. This is done through a component called ADC (Analog to Digital Converter). This will quantize the analog signal and output the value of the signal. Depending on the bit resolution of the ADC, the more precise the microcontroller can understand the analog signal but it has no relationship to how accurate the estimation is. 

In this lab we will be understanding how to read analog values from a microcontroller.

Microcontollers can not read analog voltages outside the range of [0V, 3.3V) - Depending on ADC. This is important to note as voltages that exceed this range may damage the ADC. Before working with any micro controller, understand their ADC specifications to prevent unneeded damage to it. 


Please list here and place in report (WILL BE GRADED) :
Name of Microcontroller being used: Teensy 40
Number of ADCs:2
Bit Resolution of ADC(s):13
Total number of dedicated analog pins for each ADC:10
If more than one ADC, number of analog pins shared among the ADCs:10
*/ 

#include <Arduino.h>

// Connect a potentiometer to the A0 pin. DO NOT CONNECT IT DIRECTLY from power to the pin. Please keep in mind the voltage limits of analog pins. 

#define Potentiometer A0 // This is how you define an analog pin

void setup() {
    pinMode(Potentiometer, INPUT);

    // Turn on the serial monitor
    Serial.begin(9600);
}

void loop() {
    while (1 != 0) {
        int raw_value = analogRead(Potentiometer);
        Serial.println(raw_value); // println() and print() do the same thing but print ln appends a new line character at the end of the string.
        delay(500); // Why is this needed?
        float val = map(raw_value, 0, 3.3, 0, 100);
        Serial.println(val);
    }
}

// Tip - Open the serial monitor to view the output

/* Modify the code so that the values in ther serial monitor are printing a percentage of how much the potentiometer has turned. Hint - Look up the map function */