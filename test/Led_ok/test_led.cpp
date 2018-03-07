#include "Led/Led.h"


int main (void){

  Led greenLed(29);
  Led redLed(28);
  Led blueLed(27);
  Led yellowLed(26);

  for(;;){
    greenLed.on();
    redLed.on();
    blueLed.on();
    yellowLed.on();
    delay(500);
    greenLed.off();
    redLed.off();
    blueLed.off();
    yellowLed.off();
    delay(500);
  }
  return 0 ;
}