#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include "SPI.h"
#include "driver/gpio.h"

void app_main(void) {
	
    INITSPI();
    
    while (true) {
				
        uint8_t receivedByte = READBYTE();
        printf("Received Data: %u\n",receivedByte);
       
    	
    	vTaskDelay(pdMS_TO_TICKS(100)); 
        
    }

}
