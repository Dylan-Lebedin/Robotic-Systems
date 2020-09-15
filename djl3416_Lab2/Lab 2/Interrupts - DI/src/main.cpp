/*

We've now covered Digital Outputs, and both Analog and Digital Inputs.

Digital inputs are a very easy thing to accomplish as the microcontroller has to just read the Digital signal of the line and save it in memory. In practice, it becomes a little more difficult. One inherent flaw with most microcontrollers are that they can only process one thing at a time. This means if the controller has to read the voltage of a digital line, it needs to stop everything that its doing, measure the value of pin and then continue along its program. Because of this, if the program needed to wait for a pin to recieve a digital high signal, the controller would stuck doing that for a while. Fortunately there are two mindsets developed to deal with this issue. 

The first is polling and its what is specified above. Polling is the technique of measuring an input signal at a specific time. Its a technique that is used very often as it is extremely simple to implement. Programs that use a polling style of technique are usually designed to measure signals in a known timeframe. This ensures the contoller wont be stuck for a very long time and can get back to its more important task as fast as possible.

The other is interrupts. Interrupts are a way for a controller handle digital inputs without needing to allocate actual processing power towards it. Interrupts are handled by a dedicated section on the controller and run simultaneously with the main program. When the handler is asked to watch a specific pin and the pin is triggered, the handler will pause the main program and the controller will handle the interrupt condition appropriately. In code, the contoller stops whatever its doing and runs the ISR function immediately. (Look up what an ISR is)

*/

#include <Arduino.h>
#define LED_Pin 19
#define Interrupt_Pin 12

int ISR_flag = 0;
int count = 1;
int rate;

void ISR_function();

void setup() {
    // Turn on the serial monitor
    Serial.begin(9600);

    pinMode(Interrupt_Pin, INPUT);
    pinMode(LED_Pin, OUTPUT);

    // Telling the interrupt handler to watch a pin.
    attachInterrupt(Interrupt_Pin, ISR_function, RISING);
}

void loop() {
    Serial.println("Loop");
    switch (count)
{
    case 1: // code to be executed if n = 1;
        rate = 1000;
        break;
    case 2: // code to be executed if n = 2;
        rate = 500;
        break;
    case 3:
        rate = 333;
        break;
    case 4:
        rate = 250;
        break;
    case 5:
        rate = 200;
        break;
    default: // code to be executed if n doesn't match any cases
        rate = 50;
        //ISR_flag = 0;
        break;
}
    ISR_flag = 0;
    digitalWrite(LED_Pin, HIGH);
    delay(rate);
    digitalWrite(LED_Pin, LOW);
    delay(rate);
    
}

void ISR_function(){
    // ISR_function's return type must be void and must not require any parameters
    Serial.println("Button was Pressed!");
    if(ISR_flag == 0) {
        count += 1;
        if (count > 5) {
            count = 1;
        }
        ISR_flag = 1;
    }
    
}

// Explain what this code does. Next modify this code so that the button goes through a sequence of blinking at 1Hz, 2Hz, 3Hz, 4Hz and 5Hz everytime its pressed. 