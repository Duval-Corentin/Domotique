#include "Button.h"


Button::Button(char pin): pin(pin){
    wiringPiSetup();
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_UP);
}

bool Button::state(){
    return !digitalRead(pin);
}