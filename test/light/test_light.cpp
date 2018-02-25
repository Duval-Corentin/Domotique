#include <chrono>
#include <iostream>

#include <wiringPi.h>

int main(){
    char pin = 11;
    wiringPiSetup();

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(100);
    auto start = std::chrono::system_clock::now();

    pinMode(pin, INPUT);

    while(digitalRead(pin) == 0 && (start - std::chrono::system_clock::now() < std::chrono::milliseconds(2000))){
    }
    
    std::chrono::duration<double> diff = std::chrono::system_clock::now() - start;
    std::cout << "test :" << diff.count() << std::endl;
}

