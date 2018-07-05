#include "Serial.h"
#include <glog/logging.h>
#include <unistd.h>

void Serial::begin(float baudRate){
     //log to stderr
    FLAGS_alsologtostderr = 1;
    //INFO, WARNING, ERROR, and FATAL are 0, 1, 2, and 3, respectively.
    FLAGS_minloglevel = 2;
    google::InitGoogleLogging(argv0);
    LOG(INFO)<<"Serial debugging begin!";

    //set the cooresponding GPIO pins to the I2C mode
    _gpio.pinMode(GPIO_TXD0_PIN,ALT0);
    _gpio.pinMode(GPIO_RXD0_PIN,ALT0);

    //baud rate, initial clock ferquency for uart0 can be find in /boot/config.txt
    float BAUDDIV = FUARTCLK/(16*baudRate);
    IBRD = (uint16_t)BAUDDIV;
    FBRD = (uint8_t)((BAUDDIV-(int)BAUDDIV)*64);

    ICR = 0x79F;	//clear the interrupt
    LCRH  = 0x70;   //WLEN, FEN
    CR = 0x301;     //RXE, TXE, UARTEN
	LOG(INFO)<<"Serial begin!";
}

void Serial::testFIFO(){
	ITCR = 2;
	TDR = 0x1C;
	usleep(1000);
	int data = TDR;
	LOG(INFO)<<"Data: "<<std::hex<<data;
}