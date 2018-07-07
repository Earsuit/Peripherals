/*
    Code for the linux end for the serial test
*/

#include "MiniSerial.h"
#include <iostream>

int main(int argc,char* argv[]){
    MiniSerial serial(argv[0]);
    serial.begin(115200);
    int count = 0;
    while(count<100){
        if(serial.available()){
            std::cout<<std::hex<<(int)serial.read()<<std::endl;
            count++;
        }
        serial.write(0x11);
    } 
}