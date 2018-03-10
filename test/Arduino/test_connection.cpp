#include "Arduino_slave/Arduino_slave.h"

int main(){
    Arduino_slave arduino(7, 20);

    arduino.updateData();
}