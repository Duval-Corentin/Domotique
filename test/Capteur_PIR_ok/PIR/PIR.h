#ifndef PIR_H
#define PIR_H

#include <wiringPi.h>

//   maj 22/02/2018
//   PIR  --> wp 15

class PIR{
private:
    char pin;

public:
    PIR(char pin);

    bool state();
};


#endif