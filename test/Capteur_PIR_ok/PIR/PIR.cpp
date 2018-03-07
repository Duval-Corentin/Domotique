#include "PIR.h"


PIR::PIR(char pin): pin(pin){
    wiringPiSetup();
    pinMode(pin, INPUT);
}

bool PIR::state(){
    return digitalRead(pin);
}