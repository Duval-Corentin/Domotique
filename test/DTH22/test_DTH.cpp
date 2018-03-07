#include <iostream>

#include "DTH22/DTH22.h"



int main(){

    DTH22 dth(1, 3000);


    std::cout << dth.getTemperature() << std::endl;

    std::cout << dth.getHumidity() << std::endl;

    delay(4000);

    std::cout << dth.getHumidity() << std::endl;
}
