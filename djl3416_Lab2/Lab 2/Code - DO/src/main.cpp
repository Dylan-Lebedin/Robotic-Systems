// Please enable word wrap if you haven't already


/* Welcome to Robotic systems Lab 1. Please read through the entire code and understand how it works.

    If you already know how to write in C, this will be a refresher.

    The code starts by initializing all the libraries that will be used in the code. This will tell the compiler where to look for things that are missing. Library files are split into header (*.h) and C++ (*.cpp) files. The header file is usually an overview of all the delarations of classes, variables, structures and functions that are needed. The C++ files are the initialize everything in the header file. NOTE: the header and C++ files have the exact name.

    The # before the include. These commands are called pre-processors. They are important as they tell the compiler how to work. The #include command tells the pre-processor to 'Copy and paste' all the code in that file to where the #include is refrenced. The order of #includes matters as there may be issues with how libraries refrence elements, but it shouldn't be an issue in your labs.
*/
#include <Arduino.h>
/*  
    To make your code streamlined and easy to use, use the #define pre-processor. This makes your code more readable and introduces a way to manage your code better. For any pin assignments use #define to declare them instead of making a variable. In the example below, LED_Pin is defined and anywhere the compiler sees 'LED_Pin' it replaces it with '13'. This is useful as you will not need to remember which pin was used for what purpose. 

    DO NOT USE: int LED_Pin = 13; 
    
    This shouldn't be used for several reasons. 1) Some compilers don't recognize analog pins as numbers. -> A0 isn't a number. 2) You are saving memory by not storing a useless piece of information.
*/
#define LED_Pin 13


/*
    In normal C++ you will call the function 'void main(){...}'. This is important as is shows the start of the program. There can only be 1 void main function in the entire code, however, when importing Arduino.h, it already calls the void main function and forces the use of two seperate functions: setup() and loop().

    void setup(){...}
        This is where any code that needs to be run first and once will be placed. Ususally any variables that need to be initialized will end up here.

    void loop(){...}
        This is where any code that needs to be run later and forever needs to be placed. 

    There is a difference between using these functions vs. using void main(). To visulize the heirarchy of how void main is in the Arduino header file:

    void main() {
        setup();
        while(1) {
            loop();
            if (serialEventRun) serialEventRun();
        }
    }

    NOTE: The processor stops when the main function is exitted. This could be done by placing a break statement in the main function. If one were to place a break statement in void loop(), it wouldn't exit the main function but end the loop function immediatly. (This can be used as an advantage). Also keep track of the scope of any vairables defined. Variables defined in void setup() will stay local to that function and not the loop function. 
*/
void setup() {
    
    // One of the things that NEEDS to be initialized in the setup are the pin defintions. This can be done like this:
    pinMode(LED_Pin, OUTPUT);
    // This tells the controller to set the pin to an output.
}

void loop() {
/*
    This code is straight forward. It turns the digital pin for the LED high. Now rewrite the code to make the LED blink at a rate of 10Hz.
    Need Help? Look up the function delay();
*/
    
    for (int i = 0; i <= 10; i++) {
        digitalWrite(LED_Pin, HIGH);
        delay(50);
        digitalWrite(LED_Pin, LOW);
        delay(50);
    }
}
