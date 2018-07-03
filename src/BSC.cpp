#include "BSC.h"
#include <stdint.h>
#include <unistd.h>
#define LOGURU_IMPLEMENTATION 1
#include "loguru.hpp"

void BSC::I2Csetup(int freq){
    //set the cooresponding GPIO pins to the I2C mode
    _gpio.pinMode(GPIO_I2C1_SDA_PIN,ALT0);
    _gpio.pinMode(GPIO_I2C1_SLC_PIN,ALT0);

    //SCL = core clock / CDIV 
    DIV = 150000/freq;

    _rxBufferIndex = 0;
    _rxBufferLength = 0; 

    //enable BSC
    CONTROL = I2C_ENABLE;

    _timeout = 5;
    LOG_F(DEBUG, "Starting Debugging!");
}

void BSC::write(uint8_t addr, int numOfBytes, uint8_t* data){
    ADDR = addr;
    DLEN = (uint16_t)numOfBytes;
    CONTROL |= CLEAR_FIFO;
    for(int i=0;i<numOfBytes;i++)
        FIFO = data[i];
    STATUS = CLR_STATUS;
    CONTROL |= WRITE | START_TRANS;
    waitForComplete();
}

void BSC::request(uint8_t addr, uint8_t requestRegister, int numOfBytes){
    _rxBufferIndex = 0;
    _rxBufferLength = numOfBytes;
    write(addr,1,&requestRegister);
    DLEN = (uint16_t)numOfBytes;
    CONTROL |= CLEAR_FIFO;
    STATUS = CLR_STATUS;
    CONTROL |= READ | START_TRANS;
    waitForComplete();
    for(int i=0;i<numOfBytes;i++)
        _rxBuffer[i] = FIFO; 
}

void BSC::waitForComplete(){
    int tmp = _timeout;
    while((!(STATUS & DONE)) && tmp--){
        usleep(1);
        
    }
}

uint8_t BSC::readBuffer(){
    if(_rxBufferLength > 0){
        _rxBufferLength--;
        return _rxBuffer[_rxBufferIndex++];
    }
    return 0;
}

uint8_t* BSC::getBuffer(){
    return _rxBuffer;
}

void BSC::cleanup(){
    _gpio.pinMode(GPIO_I2C1_SDA_PIN,INPUT);
    _gpio.pinMode(GPIO_I2C1_SLC_PIN,INPUT);
    _gpio.cleanup();
    Peripherals::cleanup();
}
