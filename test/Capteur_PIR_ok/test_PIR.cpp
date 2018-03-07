#include <iostream>

#include "PIR/PIR.h"

int main(){
    PIR pir_sensor(15);

    while(1){
        std::cout << "PIR :" << pir_sensor.state() << std::endl;
        delay(200);
    }

}