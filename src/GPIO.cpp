#include "GPIO.h"

void GPIO::pinMode(int pin,int func){
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
    if(GPIO_LEVEL(pin) & (1<<(PIN%31)))
        return HIGH;
    else
        return LOW;
}

void GPIO::eventDetectOn(int pin, int type){
    GPIO_EVENT(pin) |= (1<<(PIN%31));
}

void GPIO::eventDetectOff(int pin, int type){
    GPIO_EVENT(pin) &= ~(1<<(PIN%31));
}

void pullUp(){
    GPIO_PULL = 0x02;
}

void pullDown(){
    GPIO_PULL = 0x01;
}

void pullUpDownOff(){
    GPIO_PULL = 0x00;
}

void clock(int pin){
    GPIO_PULL_CLOCK(pin) = (1<<(PIN%31));
}
