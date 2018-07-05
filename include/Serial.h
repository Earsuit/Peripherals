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
#define FR *(_addr+2)
#define ILPR *(_addr+3)
#define IBRD *(_addr+4)
#define FBRD *(_addr+5)
#define LCRH *(_addr+6)
#define CR *(_addr+7)
#define IFLS *(_addr+8)
#define IMSC *(_addr+9)
#define RIS *(_addr+10)
#define MIS *(_addr+11)
#define ICR *(_addr+12)
#define DMACR *(_addr+13)
#define ITCR *(_addr+14)
#define ITIP *(_addr+15)
#define ITOP *(_addr+16)
#define TDR *(_addr+17)

#define FUARTCLK 3000000  //Hz

class Serial : protected Peripherals{
    private:
    uint32_t* _addr;
    GPIO _gpio;
    
    public:
    Serial():Peripherals(UART0_ADDR_BASE){_addr = getAddr();}
    void begin(float baudRate=115200);
    void testFIFO();
};

#endif