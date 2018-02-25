#include <string>
#include <iostream>
#include "LCD/LCD.h"

unsigned char lcd_address = 0x3f;

int main(){

    std::cout << "ok";
    LcdDisplay lcd(lcd_address);

    lcd.init();

    lcd.cls();
    lcd.displayStringAtPosition("test", 3, 10);
}
