#include "Serial.h"

int main(int argc,char* argv[]){
    Serial serial;
    serial.begin(argv[0],115200);
    serial.testFIFO();
}