#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>    //std::find
#include "Peripherals.h"
  
// Exposes the physical address defined in the passed structure using mmap on /dev/mem
int Peripherals::map_peripheral()
{
   // Open /dev/mem
   this->_bcm2837_peripheral.mem_fd = open("/dev/mem", O_RDWR|O_SYNC);
   if (this->_bcm2837_peripheral.mem_fd < 0) {
      printf("Failed to open /dev/mem, try checking permissions.\n");
      return -1;
   } 

   size_t pagesize = (size_t) sysconf (_SC_PAGESIZE);
 
   this->_bcm2837_peripheral.map = mmap(
      NULL,
      pagesize,
      PROT_READ|PROT_WRITE,
      MAP_SHARED,
      this->_bcm2837_peripheral.mem_fd,      // File descriptor to physical memory virtual file '/dev/mem'
      this->_bcm2837_peripheral.addr_p       // Address in physical map that we want this memory block to expose
   );
 
   if (this->_bcm2837_peripheral.map == MAP_FAILED) {
        perror("mmap");
        return -1;
   }
 
   this->_bcm2837_peripheral.addr = (volatile uint32_t*)this->_bcm2837_peripheral.map;
 
   return 0;
}

Peripherals::Peripherals(uint32_t address_base){
    this->_bcm2837_peripheral.addr_p = address_base;
    map_peripheral();
}

Peripherals::~Peripherals(){
    unmap_peripheral();
}

uint32_t* Peripherals::getAddr(){
    return (uint32_t*)this->_bcm2837_peripheral.addr;
}

int* Peripherals::getUsedPins(){
    return _usedPins.data();
}

int Peripherals::getNumUsedPins(){
    return _usedPins.size();
}

void Peripherals::insertPin(int pin){
    if(std::find(_usedPins.begin(),_usedPins.end(),pin) == _usedPins.end()){
        //pin not found
        _usedPins.push_back(pin);
    }
}
 
void Peripherals::unmap_peripheral(){
    munmap(this->_bcm2837_peripheral.map,  (size_t) sysconf (_SC_PAGESIZE));
    close(this->_bcm2837_peripheral.mem_fd);
}