#include "MiniSerial.h"

int main(int argc,char* argv[]){
    MiniSerial serial;
    serial.begin(argv[0],115200);
    for(int i=0;i<10;i++)
        serial.write(i);
}