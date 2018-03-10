#include <wiringPi.h>

#include "Arduino_slave/Arduino_slave.h"

int main(){
    Arduino_slave arduino(7, 20);

    for(int i = 0; i < 20; i++){
        delay(10);
        std::cout << "Temperature : " << arduino.getTemperature() << " Humidité : " << arduino.getHumidity() << " photo_moyenne : " <<(int) arduino.getPhotoAverage() << " potar : " <<(int) arduino.getPotentiometer() << std::endl;
    }

}