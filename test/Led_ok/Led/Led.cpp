#include "Led.h"

Led::Led(char pin): pin(pin), current_state(false){
    wiringPiSetup();
    pinMode (pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void Led::on(){
    digitalWrite(pin, HIGH);
    current_state = true;
}

void Led::off(){
    digitalWrite(pin, LOW);
    current_state = false;
}

bool Led::state(){
    return current_state;
}



