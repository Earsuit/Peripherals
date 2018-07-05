/*
  GPIO.h - a free library for raspberry pi 3 GPIO. 
  Version 1.0
  Created by Yudi Ren, Jan 05, 2018.
  renyudicn@outlook.com
*/

#ifndef GPIO_H_
#define GPIO_H_

#include "Peripherals.h"
#include <stdint.h>

//GPFESL0 register, the first GPIO register
#define GPIO_ADDR_BASE (BCM2837_PERI_BASE + 0x200000)  
//The following event types represent the shift of their register address from the base address
#define RISING_EDGE_DETECT 19
#define FALLING_EDGE_DETECT 22
#define HIGH_DETECT 25
#define LOW_DETECT 28
#define ASYC_RISING_EDG_DETECT 31
#define ASYC_FALLING_EDGE_DETECT 34
//Registers address
#define GPIO_PIN_MODE(PIN) *(_addr+(PIN/10))
#define GPIO_HIGH(PIN) *(_addr+((PIN<=31)?7:8))
#define GPIO_LOW(PIN) *(_addr+((PIN<=31)?10:11))
#define GPIO_LEVEL(PIN) *(_addr+((PIN<=31)?13:14))
#define GPIO_EVENT(PIN) *(_addr+((PIN<=31)?type:(type+1)))
#define GPPUD *(_addr+37)
#define GPPUDCLK(PIN) *(_addr+((PIN<=31)?38:39))

#define HIGH 1
#define LOW 0
//pin mode
#define INPUT 0
#define OUTPUT 1
#define ALT0 4
#define ALT1 5
#define ALT2 6
#define ALT3 7
#define ALT4 3
#define ALT5 2

#define UP 2
#define DOWN 1
#define OFF 0

class GPIO: protected Peripherals{
    private:
    //store the mapped memory address
    uint32_t* _addr;

    public:
    GPIO(): Peripherals(GPIO_ADDR_BASE){_addr = getAddr();}
    void pinMode(int pin,int func);
    void setHigh(int pin);
    void setLow(int pin);
    int pinLevel(int pin);
    void eventDetectOn(int pin,int type);
    void eventDetectOff(int pin,int type);
    void pull_up_off_down(int pin, int type);
    //GPIO Pull-up/down Clock Registers (GPPUDCLKn) 
    void cleanup();
};

#endif
