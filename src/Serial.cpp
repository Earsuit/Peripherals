#include "Serial.h"
#include <glog/logging.h>
#include <unistd.h>

void Serial::begin(char* argv0, float baudRate){
     //log to stderr
    FLAGS_alsologtostderr = 1;
    //INFO, WARNING, ERROR, and FATAL are 0, 1, 2, and 3, respectively.
    FLAGS_minloglevel = 0;
    google::InitGoogleLogging(argv0);
    LOG(INFO)<<"Serial debugging begin!";

    //set the cooresponding GPIO pins to the I2C mode and turn off the pull up/down resistor
    _gpio.pinMode(GPIO_TXD0_PIN,ALT0);
    _gpio.pinMode(GPIO_RXD0_PIN,ALT0);
	_gpio.pull_up_off_down(GPIO_TXD0_PIN,OFF);
	_gpio.pull_up_off_down(GPIO_RXD0_PIN,OFF);

    //baud rate, initial clock ferquency for uart0 can be find in /boot/config.txt
    float BAUDDIV = FUARTCLK/(16*baudRate);
    IBRD = (uint16_t)BAUDDIV;
    FBRD = (uint8_t)((BAUDDIV-(int)BAUDDIV)*64);

	CR = 0x00;		//disable the uart
	usleep(1000);	//wait for transmission complete
	ICR = 0x7FF;	//clear the interrupt
	LCRH &= ~0x10;	//flush FIFO
    LCRH |= 0x70;   //WLEN, FEN
    CR = 0x300;      //RXE, TXE
	CR = 1;			//UARTEN
	LOG(INFO)<<"Serial begin!";
}

void Serial::testFIFO(){
	ITCR = 2;
	TDR = 0x1C;
	usleep(5000);
	int data = DR & 0xFF;
	LOG(INFO)<<"Data: "<<std::hex<<data;
}