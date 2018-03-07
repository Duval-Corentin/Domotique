#ifndef LED_H
#define LED_H

#include <wiringPi.h>



//   maj 22/02/2018 
//   GREEN LED  --> wp 29
//   RED LED    --> wp 28
//   BLUE LED   --> wp 27
//   YELLOW LED --> wp 26

class Led{
private:
    char pin;
    bool current_state;
public:
    Led(char pin);

    void on();
    void off();

    bool state();
};

#endif // LED_H