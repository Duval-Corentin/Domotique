#include <string>
#include <iostream>
#include <wiringPi.h>
#include "LCD/LCD.h"

unsigned char lcd_address = 0x3f;

int main(){

    std::cout << "ok";
    LcdDisplay lcd(lcd_address);
    lcd.init();
    lcd.cls();
    
    while(1){

    lcd.displayStringAtPosition("test", 3, 10);

    delay(2000); 

    lcd.setBacklight(false);
    delay(1000);
    lcd.displayStringAtPosition("ok !", 2, 10);

    delay(1000);
    lcd.setBacklight(true);
    delay(2000);

    lcd.cls();
    delay(1000);
    }
}
