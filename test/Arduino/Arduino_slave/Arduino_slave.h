#ifndef ARDUINO_SLAVE_H
#define ARDUINO_SLAVE_H

#include <chrono>

#include "pi2c.h"

class Arduino_slave{
private:
    float temperature;
    float humidity;
    char photo_1;
    char photo_2;
    char photo_3;
    char potentiometer;

    std::chrono::system_clock::time_point last_request;
    std::chrono::duration<double, std::milli> request_stamp;

    Pi2c arduino;

    
    void isUpdatable();
public:
    Arduino_slave(int address, int update_time_stamp_ms);

    float getTemperature();
    float getHumidity();
    char getPhoto1();
    char getPhoto2();
    char getPhoto3();
    char getPotentiometer();

    void updateData();
};



#endif