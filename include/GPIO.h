#ifndef GPIO_H_
#define GPIO_H_

#include "Peripherals.h"

#define GPIO_BASE (BCM2837_PERI_BASE + 0x200000)  //GPFESL0 register, the first GPIO register

extern bcm2837_peripheral gpio = {GPIO_BASE};

#define GPIO_IN(PIN) *(gpio.addr+(PIN/10)) &= ~(7<<((PIN%10)*3))
#define GPIO_OUT(PIN) *(gpio.addr+(PIN/10)) = (GPIO_IN(PIN)) | (1<<((PIN%10)*3))
#define GPIO_SET(PIN) *(gpio.addr+((PIN<=31)?7:8)) = (1<<(PIN%31))    // writing a “0” to the field has no effect
#define GPIO_CLR(PIN) *(gpio.addr+((PIN<=31)?10:11)) = (1<<(PIN%31))    // writing a “0” to the field has no effect
#define GPIO_HIGH(PIN) *(gpio.addr+((PIN<=31)?13:14)) |= (1<<(PIN%31))
#define GPIO_LOW(PIN) *(gpio.addr+((PIN<=31)?13:14)) &= ~(1<<(PIN%31))
//GPIO Event Detect Status Registers (GPEDSn) 
#define GPIO_EVENT_DET_SET(PIN) *(gpio.addr+((PIN<=31)?16:17)) |= (1<<(PIN%31))
#define GPIO_EVENT_DET_CLR(PIN) *(gpio.addr+((PIN<=31)?16:17)) &= ~(1<<(PIN%31))
//GPIO Rising Edge Detect Enable Registers (GPRENn) 
#define GPIO_RISE_EDGE_SET(PIN) *(gpio.addr+((PIN<=31)?19:20)) |= (1<<(PIN%31))
#define GPIO_RISE_EDGE_CLR(PIN) *(gpio.addr+((PIN<=31)?19:20)) &= ~(1<<(PIN%31)) 
//GPIO Falling Edge Detect Enable Registers (GPRENn) 
#define GPIO_FALL_EDGE_SET(PIN) *(gpio.addr+((PIN<=31)?22:23)) |= (1<<(PIN%31))
#define GPIO_FALL_EDGE_CLR(PIN) *(gpio.addr+((PIN<=31)?22:23)) &= ~(1<<(PIN%31))
//GPIO High Detect Enable Registers (GPHENn) 
#define GPIO_HIGH_DET_SET(PIN) *(gpio.addr+((PIN<=31)?25:26)) |= (1<<(PIN%31))
#define GPIO_HIGH_DET_CLR(PIN) *(gpio.addr+((PIN<=31)?25:26)) &= ~(1<<(PIN%31))
//GPIO Low Detect Enable Registers (GPLENn) 
#define GPIO_LOW_DET_SET(PIN) *(gpio.addr+((PIN<=31)?28:29)) |= (1<<(PIN%31))
#define GPIO_LOW_DET_CLR(PIN) *(gpio.addr+((PIN<=31)?28:29)) &= ~(1<<(PIN%31))
//GPIO Asynchronous rising Edge Detect Enable Registers (GPARENn) 
#define GPIO_ASY_RISE_EDGE_SET(PIN) *(gpio.addr+((PIN<=31)?31:32)) |= (1<<(PIN%31))
#define GPIO_ASY_RISE_EDGE_CLR(PIN) *(gpio.addr+((PIN<=31)?31:32)) &= ~(1<<(PIN%31))
//GPIO Asynchronous Falling Edge Detect Enable Registers (GPAFENn) 
#define GPIO_ASY_FALL_EDGE_SET(PIN) *(gpio.addr+((PIN<=31)?34:35)) |= (1<<(PIN%31))
#define GPIO_ASY_FALL_EDGE_CLR(PIN) *(gpio.addr+((PIN<=31)?34:35)) &= ~(1<<(PIN%31))
//GPIO Pull-up/down Register (GPPUD) 
#define GPIO_PULL_UP_SET *(gpio.addr+37) = 0x02
#define GPIO_PULL_DOWN_SET *(gpio.addr+37)  = 0x01
#define GPIO_PULL_OFF *(gpio.addr+37)  = 0;
//GPIO Pull-up/down Clock Registers (GPPUDCLKn) 
#define GPIO_PULL_CLOCK(PIN) *(gpio.addr+((PIN<=31)?38:39)) = (1<<(PIN%31))  //writing 0 has no effect

class GPIO:Peripherals{
    
}

#endif
