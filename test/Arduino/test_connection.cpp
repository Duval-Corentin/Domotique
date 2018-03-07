#include "Pi2c/pi2c.h"

int main(){
    Pi2c arduino(7); //Create a new object "arduino" using address "0x07"
    char receive[16]; //Create a buffer of char (single bytes) for the data

    //Receive from the Arduino and put the contents into the "receive" char array
    arduino.i2cRead(receive,16);
     //Print out what the Arduino is sending...
    std::cout << "Arduino Says: " << (int) receive[0] << (int) receive[2] << std::endl;

    //Send an 16 bit integer
    arduino.i2cWriteArduinoInt(4356);

    return 0;
}