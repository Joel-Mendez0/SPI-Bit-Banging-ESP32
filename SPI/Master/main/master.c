#include "SPI.h"
#include "freertos/FreeRTOS.h"

uint8_t data[1000];
uint8_t receivedData[1000];

void printbuffer(uint8_t *buffer, uint32_t length){
	for(uint32_t i = 0; i < length; i++){
		printf("buffer[%lu] = %u\n",i,buffer[i]);
	}
}

void app_main(void) {

    for (int i = 0; i < 1000; i++) {
        data[i] = i % 256;
    }

    INITSPI();
    
    while(1){
	
		MASTERTRANSMIT(data, 1000);	
			
		vTaskDelay(pdMS_TO_TICKS(1000));
		
		MASTERRECEIVE(receivedData, 1000);
		
		printbuffer(receivedData,1000);
		
		vTaskDelay(pdMS_TO_TICKS(1000));
		
}}
