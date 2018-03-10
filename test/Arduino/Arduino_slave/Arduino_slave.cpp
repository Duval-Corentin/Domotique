#include <chrono>
#include <string>
#include <iostream>

#include "Arduino_slave.h"

Arduino_slave::Arduino_slave(int address, int update_time_stamp_ms): 
temperature(0), humidity(0), photo_1(0), photo_2(0), photo_3(0), last_request(std::chrono::system_clock::now()), request_stamp(std::chrono::milliseconds(update_time_stamp_ms)), arduino(Pi2c(address))
{}

void Arduino_slave::updateData(){
    char payload[16];
    this->arduino.i2cRead(payload, 16);

    this->temperature = std::stof( std::to_string((int)payload[0]) + "." + std::to_string((int)payload[1]));
    std::cout << this->temperature <<std::endl;
}