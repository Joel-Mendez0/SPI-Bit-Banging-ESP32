#include "SPI.h"
#include "freertos/FreeRTOS.h"

uint8_t data[256];

void app_main(void) {
	
	for (int i = 0; i < 256; i++) {
		data[i] = i;
		}
    INITSPI();

    while(true){
		
		TRANSMIT(data, 256);
	}
       
}