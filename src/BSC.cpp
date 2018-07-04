#include "BSC.h"
#include <stdint.h>
#include <unistd.h>
#include <glog/logging.h>

void BSC::I2Csetup(const char* argv0, int freq){
    //log to stderr
    FLAGS_alsologtostderr = 1;
    //INFO, WARNING, ERROR, and FATAL are 0, 1, 2, and 3, respectively.
    FLAGS_minloglevel = 2;
    google::InitGoogleLogging(argv0);
    LOG(INFO)<<"BSC debugging begin!";

    //set the cooresponding GPIO pins to the I2C mode
    _gpio.pinMode(GPIO_I2C1_SDA_PIN,ALT0);
    _gpio.pinMode(GPIO_I2C1_SLC_PIN,ALT0);

    // SCL = core clock / CDIV 
    DIV = CORE_CLK/freq;

    _rxBufferIndex = 0;
    _rxBufferLength = 0; 

    _timeout = TIMEOUT;
    LOG(INFO)<<"I2C setup done!";
}

void BSC::write(uint8_t addr, uint16_t numOfBytes, uint8_t* data){
    ADDR = addr;
    DLEN = numOfBytes;
    LOG(INFO)<<"Prepare to transfer "<<numOfBytes<<" bytes to "<<std::hex<<(int)addr;
    for(int i=0;i<numOfBytes;i++){
        FIFO = data[i];
        LOG(INFO)<<"data: "<<std::hex<<(int)data[i];
    }
    STATUS = CLR_STATUS;
    CONTROL = WRITE | START_TRANS | I2C_ENABLE;
    LOG(INFO)<<"Start transfering";
    waitForComplete();
}

void BSC::request(uint8_t addr, uint8_t requestRegister, uint16_t numOfBytes){
    LOG(INFO)<<"Requesting!";
    _rxBufferIndex = 0;
    _rxBufferLength = numOfBytes;
    write(addr,1,&requestRegister);

    DLEN = numOfBytes;
    STATUS = CLR_STATUS;
    CONTROL = READ | START_TRANS | I2C_ENABLE | CLEAR_FIFO;
    LOG(INFO)<<"Start to request "<<numOfBytes<<" bytes from "<<std::hex<<(int)addr<<"'s "<<std::hex<<(int)requestRegister;
    waitForComplete();
}

void BSC::waitForComplete(){
    int tmp = _timeout;
    while((!(STATUS & DONE)) && --tmp){
        usleep(1);
    }
    if(tmp==0)
        LOG(ERROR)<<"Transfer timeout";
    LOG(INFO)<<"Transfer done!";
    error();
}

uint8_t BSC::readBuffer(){
    if(STATUS & RXD)
        return FIFO;
    else{
        LOG(ERROR)<<"FIFO empty";
        return 0;
    }
}

void BSC::cleanup(){
    _gpio.pinMode(GPIO_I2C1_SDA_PIN,INPUT);
    _gpio.pinMode(GPIO_I2C1_SLC_PIN,INPUT);
    _gpio.cleanup();
    Peripherals::cleanup();
}

void BSC::error(){
    if(STATUS & CLKT)
        LOG(ERROR)<<"CLKT Clock Stretch Timeout.";
    else if(STATUS & ERR)
        LOG(ERROR)<<"ERR ACK Error.";
}
