#ifndef SERIAL_H_
#define SERIAL_H_

#include "Peripherals.h"
#include <stdint.h>
#include "GPIO.h"

#define UART0_ADDR_BASE (BCM2837_PERI_BASE + 0x201000) 
#define GPIO_TXD0_PIN 14 
#define GPIO_RXD0_PIN 15

#define DR *_addr
#define RSRECR *(_addr+1)
#define FR *(_addr+6)
#define ILPR *(_addr+8)
#define IBRD *(_addr+9)
#define FBRD *(_addr+10)
#define LCRH *(_addr+11)
#define CR *(_addr+12)
#define IFLS *(_addr+13)
#define IMSC *(_addr+14)
#define RIS *(_addr+15)
#define MIS *(_addr+16)
#define ICR *(_addr+17)
#define DMACR *(_addr+18)
#define ITCR *(_addr+32)
#define ITIP *(_addr+33)
#define ITOP *(_addr+34)
#define TDR *(_addr+35)

#define FUARTCLK 3000000  //Hz

class Serial : protected Peripherals{
    private:
    uint32_t* _addr;
    GPIO _gpio;
    
    public:
    Serial():Peripherals(UART0_ADDR_BASE){_addr = getAddr();}
    void begin(char* argv0,float baudRate=115200);
    void testFIFO();
};

#endif