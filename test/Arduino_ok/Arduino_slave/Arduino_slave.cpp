#include <chrono>
#include <string>
#include <iostream>

#include "Arduino_slave.h"

Arduino_slave::Arduino_slave(int address, int update_time_stamp_ms): 
temperature(0), humidity(0), photo_1(0), photo_2(0), photo_3(0), last_request(std::chrono::system_clock::now()), request_stamp(std::chrono::milliseconds(update_time_stamp_ms)), arduino(Pi2c(address))
{}

void Arduino_slave::updateData(){
    if(isUpdatable()){
        char payload[16];
        this->arduino.i2cRead(payload, 16);

        this->temperature = std::stof( std::to_string((int)payload[0]) + "." + std::to_string((int)payload[1]));
        this->humidity = std::stof( std::to_string((int)payload[2]) + "." + std::to_string((int)payload[3]));
        this->photo_1 = payload[4];
        this->photo_2 = payload[5];
        this->photo_3 = payload[6];
        this->potentiometer = payload[7];

        this->last_request = std::chrono::system_clock::now();
    }
}

bool Arduino_slave::isUpdatable(){
    if( (std::chrono::system_clock::now() - this->last_request ) > std::chrono::milliseconds(30)){
        return true;
    } else{
        return false;
    }
}

float Arduino_slave::getTemperature(){
    updateData();
    return this->temperature;
}

float Arduino_slave::getHumidity(){
    updateData();
    return this->humidity;
}

char Arduino_slave::getPhoto1(){
    updateData();
    return this->photo_1;
}

char Arduino_slave::getPhoto2(){
    updateData();
    return this->photo_2;
}

char Arduino_slave::getPhoto3(){
    updateData();
    return this->photo_3;
}

char Arduino_slave::getPotentiometer(){
    updateData();
    return this->potentiometer;
}

char Arduino_slave::getPhotoAverage(){
    updateData();
    return (this->photo_1 + this->photo_2 + this->photo_3) / 3;
} 