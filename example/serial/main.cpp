/*
    Code for the linux end for the serial test
*/

#include "MiniSerial.h"
#include <iostream>

int main(int argc,char* argv[]){
    MiniSerial serial(argv[0]);
    serial.begin(115200);
    uint8_t buffer[10];
    serial.flush();
    int count = serial.read(buffer,10);
    std::cout<<"N: "<<count<<std::endl;
    for(int i=0;i<count;i++)
        std::cout<<int(buffer[i])<<std::endl;
}