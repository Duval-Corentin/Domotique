#ifndef BUTTON_H
#define BUTTON_H

#include <wiringPi.h>

//   maj 22/02/2018
//   BUTTON 1 --> wp 21
//   BUTTON 2 --> wp 22
//   BUTTON 3 --> wp 23
//   BUTTON 4 --> wp 24 
//   BUTTON 5 --> wp 25


class Button{
private:
    char pin;

public: 
    Button(char pin);

    bool state();
};

#endif //BUTTON_H