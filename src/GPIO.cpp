#include "GPIO.h"

GPIO::~GPIO(){
    int* pins = getUsedPins();
    int size = getNumUsedPins();
    for(int i=0;i<size;i++){
        pinMode(pins[i],INPUT);
        pull_up_off_down(pins[i],DOWN);
    }
}

void GPIO::pinMode(int pin,int func){
    //add to used pins
    insertPin(pin);
    //Actually, the ALT3 in the first line has no meaning, what we really need 
    // is 111 in binary(7 in decimal), which makes the first command clear the bits
    GPIO_PIN_MODE(pin) &= ~(ALT3<<((pin%10)*3));
    GPIO_PIN_MODE(pin) |= (func<<((pin%10)*3));
}

void GPIO::setHigh(int pin){
    GPIO_HIGH(pin) = (1<<(pin%31));
}

void GPIO::setLow(int pin){
    GPIO_LOW(pin) = (1<<(pin%31));
}

int GPIO::pinLevel(int pin){
    if(GPIO_LEVEL(pin) & (1<<(pin%31)))
        return HIGH;
    else
        return LOW;
}

void GPIO::eventDetectOn(int pin, int type){
    GPIO_EVENT(pin) |= (1<<(pin%31));
}

void GPIO::eventDetectOff(int pin, int type){
    GPIO_EVENT(pin) &= ~(1<<(pin%31));
}

void GPIO::pull_up_off_down(int pin,int type){
    GPPUD = type;
    for(int i=0;i<150;i++);
    GPPUDCLK(pin) = (1<<(pin%31));
    for(int i=0;i<150;i++);
    GPPUDCLK(pin) = 0x00;
}
