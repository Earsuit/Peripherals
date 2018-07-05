#ifndef BSC_H_
#define BSC_H_

#include "Peripherals.h"
#include <stdint.h>
#include "GPIO.h"
#include <glog/logging.h>

#define BSC1_ADDR_BASE (BCM2837_PERI_BASE + 0x804000) 
#define GPIO_I2C1_SDA_PIN 2 
#define GPIO_I2C1_SLC_PIN 3

//the following are the registers 
#define CONTROL *_addr
#define STATUS *(_addr+1)
#define DLEN *(_addr+2)
#define ADDR *(_addr+3)
#define FIFO *(_addr+4)
#define DIV *(_addr+5)
#define DEL *(_addr+6)
#define CLTK *(_addr+7)

//Control register command
#define I2C_ENABLE 0x8000
#define INTR 0x400
#define INTT 0x200
#define INTD 0x100
#define START_TRANS 0x80
#define CLEAR_FIFO 0x20
#define READ 0x1
#define WRITE 0

//STATUS register command
#define CLKT 0x200
#define ERR 0x100
#define RXF 0x80
#define TXE 0x40
#define RXD 0x20
#define TXD 0x10
#define RXR 0x8
#define TXW 0x4
#define DONE 0x2
#define TA 1
#define CLR_STATUS (CLKT | ERR | DONE)

#define CORE_CLK 150000  //kHz
#define TIMEOUT 5000  //timeout, 5000 microsecond

class BSC: protected Peripherals{
    private:
    uint32_t* _addr;
    GPIO _gpio;
    int _timeout;

    public:
    BSC():Peripherals(BSC1_ADDR_BASE){_addr = getAddr();}
    void I2Csetup(const char* argv0,int freq=100);  //unit khz
    void write(uint8_t addr, uint16_t numOfBytes, uint8_t* data);
    void request(uint8_t addr, uint8_t requestRegister, uint16_t numOfBytes);
    void waitForComplete();
    uint8_t readBuffer();
    void cleanup();
    void error();
    
};

#endif