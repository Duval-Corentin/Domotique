#include <vector>
#include <iostream>
#include "Button/Button.h"

int main(){
    std::vector<Button> buttons;

    for(int i = 25; i > 20; i--){
        buttons.push_back(Button(i));
    }

    while(1){
        for(int i = 0; i < 5; i++){
            std::cout << " B" << i << " : " << buttons[i].state();
        }
        std::cout << std::endl;
        delay(100);
    }

}