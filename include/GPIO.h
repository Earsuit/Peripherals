#ifndef GPIO_H_
#define GPIO_H_

#include "Peripherals.h"
#include <stdint.h>

// #define GPIO_IN(PIN) *(gpio.addr+(PIN/10)) &= ~(7<<((PIN%10)*3))
// #define GPIO_OUT(PIN) *(gpio.addr+(PIN/10)) = (GPIO_IN(PIN)) | (1<<((PIN%10)*3))
// #define GPIO_SET(PIN) *(gpio.addr+((PIN<=31)?7:8)) = (1<<(PIN%31))    // writing a “0” to the field has no effect
// #define GPIO_CLR(PIN) *(gpio.addr+((PIN<=31)?10:11)) = (1<<(PIN%31))    // writing a “0” to the field has no effect
// #define GPIO_LEVEL(PIN) *(gpio.addr+((PIN<=31)?13:14)) & (1<<(PIN%31))
// //GPIO Rising Edge Detect Enable Registers (GPRENn) 
// #define GPIO_RISE_EDGE_SET(PIN) *(gpio.addr+((PIN<=31)?19:20)) |= (1<<(PIN%31))
// #define GPIO_RISE_EDGE_CLR(PIN) *(gpio.addr+((PIN<=31)?19:20)) &= ~(1<<(PIN%31)) 
// //GPIO Falling Edge Detect Enable Registers (GPRENn) 
// #define GPIO_FALL_EDGE_SET(PIN) *(gpio.addr+((PIN<=31)?22:23)) |= (1<<(PIN%31))
// #define GPIO_FALL_EDGE_CLR(PIN) *(gpio.addr+((PIN<=31)?22:23)) &= ~(1<<(PIN%31))
// //GPIO High Detect Enable Registers (GPHENn) 
// #define GPIO_HIGH_DET_SET(PIN) *(gpio.addr+((PIN<=31)?25:26)) |= (1<<(PIN%31))
// #define GPIO_HIGH_DET_CLR(PIN) *(gpio.addr+((PIN<=31)?25:26)) &= ~(1<<(PIN%31))
// //GPIO Low Detect Enable Registers (GPLENn) 
// #define GPIO_LOW_DET_SET(PIN) *(gpio.addr+((PIN<=31)?28:29)) |= (1<<(PIN%31))
// #define GPIO_LOW_DET_CLR(PIN) *(gpio.addr+((PIN<=31)?28:29)) &= ~(1<<(PIN%31))
// //GPIO Asynchronous rising Edge Detect Enable Registers (GPARENn) 
// #define GPIO_ASY_RISE_EDGE_SET(PIN) *(gpio.addr+((PIN<=31)?31:32)) |= (1<<(PIN%31))
// #define GPIO_ASY_RISE_EDGE_CLR(PIN) *(gpio.addr+((PIN<=31)?31:32)) &= ~(1<<(PIN%31))
// //GPIO Asynchronous Falling Edge Detect Enable Registers (GPAFENn) 
// #define GPIO_ASY_FALL_EDGE_SET(PIN) *(gpio.addr+((PIN<=31)?34:35)) |= (1<<(PIN%31))
// #define GPIO_ASY_FALL_EDGE_CLR(PIN) *(gpio.addr+((PIN<=31)?34:35)) &= ~(1<<(PIN%31))
// //GPIO Pull-up/down Register (GPPUD) 
// #define GPIO_PULL_UP_SET *(gpio.addr+37) = 0x02
// #define GPIO_PULL_DOWN_SET *(gpio.addr+37)  = 0x01
// #define GPIO_PULL_OFF *(gpio.addr+37)  = 0;
// //GPIO Pull-up/down Clock Registers (GPPUDCLKn) 
// #define GPIO_PULL_CLOCK(PIN) *(gpio.addr+((PIN<=31)?38:39)) = (1<<(PIN%31))  //writing 0 has no effect

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
#define GPIO_PULL *(_addr+37)
#define GPIO_PULL_CLOCK(PIN) *(_addr+((PIN<=31)?38:39))

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

class GPIO: protected Peripherals{
    private:
    uint32_t* _addr;

    public:
    GPIO(): Peripherals(GPIO_ADDR_BASE){_addr = getAddr();}
    void pinMode(int pin,int func);
    void setHigh(int pin);
    void setLow(int pin);
    int pinLevel(int pin);
    void eventDetectOn(int pin,int type);
    void eventDetectOff(int pin,int type);
    void pullUp();
    void pullDown();
    void pullUpDownOff();
    //GPIO Pull-up/down Clock Registers (GPPUDCLKn) 
    void clock(int pin);
    void cleanup();
};

#endif
