#include "Peripherals.h"
#include "GPIO.h"
#include <unistd.h>

int main(int argc,char* argv[]){
    if(map_peripheral(&gpio) == -1)
        return 0;
   
    GPIO_OUT(4);
 
    GPIO_SET(4);
    sleep(1);
    GPIO_CLR(4);
    sleep(1);

    unmap_peripheral(&gpio);
    
    return 0;
}
