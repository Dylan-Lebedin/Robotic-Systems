/* This code will guide you through how to output analog signals. Dealing with signals in the digital world is important and can allow us to be efficient in communication. There are times, however, where we will need to generate an analog signal. There are multiple ways to generate an analog signal and we will discuss both ways. 

One way is to use a module called a DAC. This is a Digital to Analog converter and it will allow us to communicate to it and tell it to produce an exact voltage. DACs are extremely powerful and accurate. Similar to the ADC, a DAC has a bit resolution specification which will tell you it's accuracy. The higher the resolution, the smaller voltage differences it can create. One issue with a DAC is that they are not common place. Having a decent DAC on a microcontroller can be expensive and is usually not needed in day to day applications. For this and many more reasons, most microcontrollers don't have it.

The second way is to simulate an analog signal with a digital signal through a method called PWM. PWM stands for pulse width modulation and as the name says, it allows a controller to vary the width of a pulse signal. For a PWM signal, a microcontroller creates a pulse train at a certain frequency. The ratio of when this pulse is on to off in one period is called Duty cycle. When passed through a low pass filter, the end result will be an analog signal. A PWM signal is strictly a digital signal and most microcontrollers use this to output an analog signal.

NOTE: Note all pins on a microcontroller can generate PWM signals. Please look at your microntroller's data sheet to understand which pins are capable. 
*/

#include <Arduino.h>
#define LED_Pin 19

void setup() {
    pinMode(LED_Pin, OUTPUT);
    delay(100);

    /*
        To generate an analog signal use the analogWrite() function. Please look it up and understand the arguments. If the pin is a PWM pin, it will generate a PWM signal. If the Pin is a DAC pin, it will generate a true analog signal. 
    */
    

    /* Place an LED and a resistor on the LED_Pin and show that the LED will dim.*/
}

/* Next: Modify the code to generate a 20Hz triangle signal and output it both as a PWM signal and on the DAC. Compare the two on an Oscilloscope.*/

void loop() {
    for (int i = 0; i < 250; i += 5) {
            analogWrite(LED_Pin, i);
            delay(0.5);
    }
    for (int i = 250; i > 0; i -= 5) {
            analogWrite(LED_Pin, i);
            delay(0.5);
    }
}