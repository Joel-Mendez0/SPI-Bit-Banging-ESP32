/*
 * SPI.c (slave)
 *
 *  Created on: Aug 25, 2024
 *      Author: Joel
 */

#include "SPI.h"
#include "freertos/FreeRTOS.h"
#include <unistd.h>

void INITSPI(void) {
	
    gpio_set_direction(SCLKPIN, GPIO_MODE_INPUT);  // Slave reads the clock signal
    
    gpio_set_direction(MOSIPIN, GPIO_MODE_INPUT);  // Slave reads the MOSI
    
    gpio_set_direction(MISOPIN, GPIO_MODE_OUTPUT);

    gpio_set_direction(CSPIN, GPIO_MODE_INPUT);    // Slave reads the chip select signal   

	gpio_set_level(MISOPIN, 0);
	
	vTaskDelay(pdMS_TO_TICKS(1000));
}

void SLAVERECEIVE(uint8_t *buffer, uint32_t length) {
    
	while(gpio_get_level(CSPIN) == 1) {}
	
	gpio_set_level(MISOPIN, 1); // Signal to Master that Slave is ready
		
    for (uint32_t j = 0; j < length; j++) {
        uint8_t receivedByte = 0;

        for (uint8_t i = 0; i < 8; i++) {
			
            while (gpio_get_level(SCLKPIN) != 0) {} // Wait for clock to be low
            
            receivedByte <<= 1; // Shift bit for next placement
            
            usleep(5); // Delay to guarantee MOSI pin is correct

            receivedByte |= gpio_get_level(MOSIPIN);  // Read MOSI bit
          
            while (gpio_get_level(SCLKPIN) != 1) {} // Wait for clock to be high
            
        }

        buffer[j] = receivedByte; // add byte to buffer
    }
    
    gpio_set_level(MISOPIN, 0); // Signal that Slave is done
}

void SLAVETRANSMIT(uint8_t *data, uint32_t length) {
	
	while(gpio_get_level(CSPIN) == 1 && gpio_get_level(MOSIPIN) != 1) {} // Wait for master to select slave
	
	gpio_set_level(MISOPIN,1); // Signal to master that slave is ready 
	
    for (uint32_t j = 0; j < length; j++) {
			
			uint8_t byteToSend = data[j];
        
        for (uint8_t i = 0; i < 8; i++) {
			
			while(gpio_get_level(SCLKPIN) != 1){} // Wait for clock high
			
			gpio_set_level(MISOPIN, (byteToSend & 0x80) ? 1 : 0);
			
			byteToSend <<= 1;
			
			while(gpio_get_level(SCLKPIN) != 0){} // Wait for clock low
			
        }
    }
}
