#include "MiniSerial.h"
#include <glog/logging.h>
#include <unistd.h>

void MiniSerial::begin(uint32_t baudRate){
    //set the cooresponding GPIO pins to the I2C mode and turn off the pull up/down resistor
    _gpio.pinMode(GPIO_TXD1_PIN,ALT5);
    _gpio.pinMode(GPIO_RXD1_PIN,ALT5);
	_gpio.pull_up_off_down(GPIO_TXD1_PIN,UP);
	_gpio.pull_up_off_down(GPIO_RXD1_PIN,UP);
    
    //enable uart
    AUX_ENABLES = UART_ENABLE;
    //baud rate
    AUX_MU_BAUD_REG = SYSTEM_CLK_FREQ/(8*baudRate)-1;
    LOG(INFO)<<AUX_MU_BAUD_REG;
    //Data size
    AUX_MU_LCR_REG = DATA_SIZE_8;
    //Transmitter & receiver enable
    AUX_MU_CNTL_REG = TRANSMITTER_ENABLE | RECEIVER_ENABLE;
    LOG(INFO)<<"Serial begin!";
}

void MiniSerial::write(uint8_t data){
	AUX_MU_IO_REG = data;
    //wait for complete
    while(!(AUX_MU_STAT_REG & TRANS_DONE));
}

bool MiniSerial::available(){
    return AUX_MU_STAT_REG & DATA_READY;
}

void MiniSerial::flush(){
    AUX_MU_IIR_REG = FLUSH_RECE_FIFO;
}

uint8_t MiniSerial::read(){
    return AUX_MU_IO_REG;
}