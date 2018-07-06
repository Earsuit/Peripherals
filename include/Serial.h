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

//DR register mask
#define OE (1<<11)
#define BE (1<<10)
#define PE (1<<9)
#define FE (1<<8)
#define DATA 0xFF

//FR register mask
#define TXFE (1<<7)
#define RXFF (1<<6)
#define TXFF (1<<5)
#define RXFE (1<<4)
#define BUSY (1<<3)

//CR register mask
#define CTSEN (1<<15)
#define RTSEN (1<<14)
#define RTS (1<<11)
#define DTR (1<<10)
#define RXE (1<<9)
#define TXE (1<<8)
#define LBE (1<<7)
#define UARTEN 1

//LCRH register mask
#define SPS (1<<7)
#define WLEN_8 0x60
#define WLEN_7 0x40
#define WLEN_6 0x20
#define WLEN_5 0x00
#define FEN (1<<4)
#define STP2 (1<<3)
#define EPS (1<<2)
#define PEN (1<<1)
#define BRK 1

#define FUARTCLK 3000000  //Hz

class Serial : protected Peripherals{
    private:
    uint32_t* _addr;
    GPIO _gpio;
    
    public:
    Serial():Peripherals(UART0_ADDR_BASE){_addr = getAddr();}
    void begin(char* argv0,float baudRate=115200);
    void testFIFO();
    bool available();
    void write(uint8_t data);
};

#endif