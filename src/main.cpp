#include "Peripherals.h"
#include "GPIO.h"
#include <unistd.h>

int main(int argc,char* argv[]){
    GPIO gpio;
    gpio.pinMode(4,OUTPUT);
    gpio.setHigh(4);
    sleep(1);
    gpio.setLow(4);
    sleep(1);
    gpio.setHigh(4);
    sleep(1);
    gpio.setLow(4);

    gpio.cleanup();
    
    return 0;
}
