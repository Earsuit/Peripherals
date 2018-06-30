#include <stdio.h>
 
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
 
#include <unistd.h>
#include <fcntl.h>
#include "Peripherals.h"
  
// Exposes the physical address defined in the passed structure using mmap on /dev/mem
int Peripherals::map_peripheral()
{
   // Open /dev/mem
   this->bcm2837_peripheral.mem_fd = open("/dev/mem", O_RDWR|O_SYNC);
   if (this->bcm2837_peripheral.mem_fd < 0) {
      printf("Failed to open /dev/mem, try checking permissions.\n");
      return -1;
   }

   size_t pagesize = (size_t) sysconf (_SC_PAGESIZE);
 
   this->bcm2837_peripheral.map = mmap(
      NULL,
      pagesize,
      PROT_READ|PROT_WRITE,
      MAP_SHARED,
      this->bcm2837_peripheral.mem_fd,      // File descriptor to physical memory virtual file '/dev/mem'
      this->bcm2837_peripheral.addr_p       // Address in physical map that we want this memory block to expose
   );
 
   if (this->bcm2837_peripheral.map == MAP_FAILED) {
        perror("mmap");
        return -1;
   }
 
   this->bcm2837_peripheral.addr = (volatile unsigned int *)this->bcm2837_peripheral.map;
 
   return 0;
}
 
void Peripherals::unmap_peripheral() {
    munmap(this->bcm2837_peripheral.map,  (size_t) sysconf (_SC_PAGESIZE));
    close(this->bcm2837_peripheral.mem_fd);
}

Peripherals::Peripherals(){
    map_peripheral();
    numOfPins = 0;
}

void insertPin(int pin){
    numOfPins++;
    usedPins = realloc(usedPins,numOfPins*sizeof(int));
}

void Peripherals::cleanup(){
    unmap_peripheral();
    free(usedPins);
    numOfPins = 0;
}
