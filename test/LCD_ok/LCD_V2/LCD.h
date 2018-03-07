#ifndef LCD_H
#define LCD_H

#include <string>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <iostream>


// Define some device constants
#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line
#define LINE3  0x94 // 3nd line
#define LINE4  0xD4 // 4nd line

#define LCD_BACKLIGHT_ON   0x08  // On
#define LCD_BACKLIGHT_OFF  0x00 // Off

#define ENABLE  0b00000100 // Enable bit 

class LCD{
private:
    char lcd_addr;
    bool backlight_state;

    void lcd_byte(int bits, int mode);
    void lcd_toggle_enable(int bits);
    void set_line(char line);
    void go_home();
    void put_char(char val);

public: 
    void init(void);
    void backlight(bool state);
    void write(char line, std::string);
    
};


#endif