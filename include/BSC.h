#ifndef BSC_H_
#define BSC_H_

#include "Peripherals.h"
#include <stdint.h>
#include "GPIO.h"
#include <glog/logging.h>

#define BSC1_ADDR_BASE (BCM2837_PERI_BASE + 0x804000) 
#define GPIO_I2C1_SDA_PIN 2 
#define GPIO_I2C1_SLC_PIN 3

#define RX_BUFFER_SIZE 32

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
#define INT_ON_RX 0x400
#define INT_ON_TX 0x200
#define INT_ON_DONE 0x100
#define START_TRANS 0x80
#define CLEAR_FIFO 0x30
#define READ 1
#define WRITE 0

//Status register command
#define CLR_STATUS 0x302
#define DONE 1

class BSC: protected Peripherals{
    private:
    uint32_t* _addr;
    uint8_t _rxBuffer[RX_BUFFER_SIZE];
    uint8_t _rxBufferIndex;
    uint8_t _rxBufferLength;
    GPIO _gpio;
    int _timeout;

    public:
    BSC():Peripherals(BSC1_ADDR_BASE){_addr = getAddr();}
    void loggingSetup(const char* argv0);
    void I2Csetup(int freq=100);  //unit khz
    void write(uint8_t addr, int numOfBytes, uint8_t* data);
    void request(uint8_t addr, uint8_t requestRegister, int numOfBytes);
    void waitForComplete();
    uint8_t readBuffer();
    uint8_t* getBuffer();
    void cleanup();
};

#endif