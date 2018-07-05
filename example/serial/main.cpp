#include "Serial.h"

int main(int argc,char* argv[]){
    Serial serial;
    serial.begin(115200);
    serial.testFIFO();
}