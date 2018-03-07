#ifndef DTH22_H
#define DTH22_H

#include <chrono>
#include <iostream>

#include <wiringPi.h>

#define MAX_TIMINGS 85


class DTH22{
private:
    char pin;
    std::chrono::duration<double> tempo;
    std::chrono::time_point<std::chrono::system_clock> last_mesure;
    char humidity;
    char temperature;

    void updateData();
public:
    DTH22(char pin, int tempo);

    char getHumidity();
    char getTemperature();
};


#endif