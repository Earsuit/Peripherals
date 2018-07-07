/*
    When the deconstuctor of this class is invoked, the uart pins will be set to input mode and turn on pull 
    down resistor, which will cause the receiver think there is a new start bit (HIGH -> LOW), and the data 
    following this start bit is 0x00.
*/

#ifndef MINI_SERIAL_H_
#define MINI_SERIAL_H_

#include "Peripherals.h"
#include <stdint.h>
#include "GPIO.h"
#include <glog/logging.h>

#define AUX_ADDR_BASE (BCM2837_PERI_BASE + 0x215000) 
#define SYSTEM_CLK_FREQ 250000000   //250MHz
#define GPIO_TXD1_PIN 14 
#define GPIO_RXD1_PIN 15

#define AUX_IRQ *(_adde)
#define AUX_ENABLES *(_addr+1)
#define AUX_MU_IO_REG *(_addr+16)
#define AUX_MU_IER_REG *(_addr+17)
#define AUX_MU_IIR_REG *(_addr+18)
#define AUX_MU_LCR_REG *(_addr+19)
#define AUX_MU_MCR_REG *(_addr+20)
#define AUX_MU_LSR_REG *(_addr+21)
#define AUX_MU_MSR_REG *(_addr+22)
#define AUX_MU_SCRATCH *(_addr+23)
#define AUX_MU_CNTL_REG *(_addr+24)
#define AUX_MU_STAT_REG *(_addr+25)
#define AUX_MU_BAUD_REG *(_addr+26)

//AUX_ENABLES register mask
#define UART_ENABLE 1

//AUX_MU_LCR_REG register mask
#define DLAB_ACCESS (1<<7)
#define BREAK (1<<6)
#define DATA_SIZE_8 0x3
#define DATA_SIZE_7 0

//AUX_MU_STAT_REG
#define TRANS_FIFO_LEVEL ((AUX_MU_STAT_REG & 0xF000000)>>24)
#define RECE_FIFO_LEVEL ((AUX_MU_STAT_REG & 0xF0000)>>16)
#define TRANS_DONE (1<<9)
#define TRANS_FIFO_EMPTY (1<<8)
#define CTS_LINE (1<<7)
#define RTS_STSTUS (1<<6)
#define TRANS_FIFO_FULL (1<<5)
#define RECEIVER_OVERRUN (1<<4)
#define TRANSMITTER_IDLE (1<<3)
#define RECEIVER_IDLE (1<<2)
#define TRANS_FIFO_AVAILABLE (1<<1)
#define DATA_READY 1

//AUX_MU_CNTL_REG register mask
#define TRANSMITTER_ENABLE (1<<1)
#define RECEIVER_ENABLE 1

//AUX_MU_IIR_REG register mask
#define FLUSH_TRANS_FIFO 0x4
#define FLUSH_RECE_FIFO 0x2

class MiniSerial : protected Peripherals{
    private:
    uint32_t* _addr;
    GPIO _gpio;

    public:
    MiniSerial(const char* argv0):Peripherals(AUX_ADDR_BASE){
        _addr = getAddr();
        //log to stderr
        FLAGS_alsologtostderr = 1;
        //INFO, WARNING, ERROR, and FATAL are 0, 1, 2, and 3, respectively.
        FLAGS_minloglevel = 0;
        google::InitGoogleLogging(argv0);
        LOG(INFO)<<"Serial debugging begin!";
    }
    void begin(uint32_t baudRate);
    void write(uint8_t data);
    bool available();
    void flush();
    uint8_t read();
};


#endif