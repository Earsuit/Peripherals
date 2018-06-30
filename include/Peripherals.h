#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_
 
#define BCM2837_PERI_BASE 0x3F000000
 
class Peripherals{
    private:
    static int* usedPins;
    int numOfPins;
    // IO Acces
    struct{
        unsigned long addr_p;
        int mem_fd;
        void *map;
        volatile unsigned int *addr;
    }bcm2837_peripheral;

	int map_peripheral();
	void unmap_peripheral();

    protected:
	Peripherals();
	//add used pin to the usedPin array
	void insertPin(int pin);
	void cleanup();
}

#endif
