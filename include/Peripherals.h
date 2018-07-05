#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include <vector>
#include <stdint.h>
 
#define BCM2837_PERI_BASE 0x3F000000
 
class Peripherals{
    private:
    std::vector<int> _usedPins;
    struct{
        uint32_t addr_p;
        int mem_fd;
        void *map;
        volatile uint32_t *addr;
    }_bcm2837_peripheral;
	int map_peripheral();

    protected:
    Peripherals(uint32_t address_base);
    ~Peripherals();
    uint32_t* getAddr();
	//add used pin to the usedPin array
    int* getUsedPins();
    int getNumUsedPins();
	void insertPin(int pin);
    void unmap_peripheral();
};

#endif
