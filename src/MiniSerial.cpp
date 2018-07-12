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
    //Data size
    AUX_MU_LCR_REG = DATA_SIZE_8;
    //Transmitter & receiver enable
    AUX_MU_CNTL_REG = TRANSMITTER_ENABLE | RECEIVER_ENABLE;

    _timeout = DEFAULT_TIMEOUT;

    LOG(INFO)<<"Serial begin!";
}

void MiniSerial::write(uint8_t data){
	AUX_MU_IO_REG = data;
    //wait for complete
    while(!(AUX_MU_STAT_REG & TRANS_DONE));
}

void MiniSerial::write(uint8_t* data,int num){
    LOG(INFO)<<"Begin writting buffer!";
    int index = 0;
    while(num>0){
        int spareFIFO = MAX_FIFO - TRANS_FIFO_LEVEL;
        LOG(INFO)<<"Spare FIFO: "<<spareFIFO;
        //if the num is less than the empty FIFO space, write them all 
        spareFIFO = spareFIFO<num?spareFIFO:num;
        for(int i=0;i<spareFIFO;i++)
            AUX_MU_IO_REG = data[index++];
        num = num>spareFIFO?(num-spareFIFO):0;
        LOG(INFO)<<"Remaining bytes after a cycle: "<<num;
    }
    while(!(AUX_MU_STAT_REG & TRANS_DONE));
    LOG(INFO)<<"Writing buffer done";
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

void MiniSerial::setTimeout(int timeout){
    _timeout = timeout;
}

int MiniSerial::read(uint8_t* buffer, int num){
    int count = 0;
    int tmp = _timeout;
    while( count!=num && tmp != 0){
        if(available()){
            buffer[count++] = AUX_MU_IO_REG;
            LOG(INFO)<<buffer[count-1];
        }else{
            tmp--;
            usleep(1);   //1us
        }
        if(tmp==0)
            LOG(WARNING)<<"Read timeout.";       
    }
    return count;
}