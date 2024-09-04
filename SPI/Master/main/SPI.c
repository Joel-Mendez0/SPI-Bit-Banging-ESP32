/*
 * SPI.c (master)
 *
 *  Created on: Aug 25, 2024
 *      Author: Joel
 */

#include "SPI.h"
#include "freertos/FreeRTOS.h"
#include <unistd.h>

void INITSPI(void) {
	
    gpio_set_direction(SCLKPIN, GPIO_MODE_OUTPUT);
    
    gpio_set_direction(MOSIPIN, GPIO_MODE_OUTPUT);
    
    gpio_set_direction(MISOPIN, GPIO_MODE_INPUT); // Master reads MISO
    
    gpio_set_direction(CSPIN, GPIO_MODE_OUTPUT);
    
    gpio_set_level(CSPIN, 1);
    
    gpio_set_level(SCLKPIN, 0);
    
    gpio_set_level(MOSIPIN,0);
    
    vTaskDelay(pdMS_TO_TICKS(1000));
   
}

void MASTERTRANSMIT(uint8_t *data, uint32_t length) {
	
    gpio_set_level(CSPIN, 0);  // Select the slave
    
    while(gpio_get_level(MISOPIN) != 1){} // Wait for Slave Signal 
    
    for (uint32_t j = 0; j < length; j++) {
		
        uint8_t byteToSend = data[j];  // Read the byte to send
        //printf("Sending byte: %u\n", byteToSend);

        for (uint8_t i = 0; i < 8; i++) {
			
            gpio_set_level(MOSIPIN, (byteToSend & 0x80) ? 1 : 0);  // Set MOSI according to the MSB

            gpio_set_level(SCLKPIN, 0);  // Clock low (active edge, falling)
            
            usleep(10); // Allow Clock to be pulled low

            byteToSend <<= 1;  // Shift the byte to the left to get the next bit

            gpio_set_level(SCLKPIN, 1);  // Clock high (idle edge, rising)
			usleep(10); // // Allow Clock to be pulled high
        }
    }

    gpio_set_level(CSPIN, 1);  // Deselect the slave
}

void MASTERRECEIVE(uint8_t *buffer, uint32_t length) {
	
	gpio_set_level(CSPIN,0); // Select Slave
	
	gpio_set_level(MOSIPIN,1); // Slave reads MOSI to verify request
	
	while(gpio_get_level(MISOPIN) != 1) {} // Wait for Slave to be ready

    for (uint32_t j = 0; j < length; j++) {
        
        uint8_t receivedByte = 0;

        for (uint8_t i = 0; i < 8; i++) {
			
			gpio_set_level(SCLKPIN,1); // Reads on Rising
			receivedByte <<= 1; // Shift byte to read next pin
			
			usleep(10); // delay for clock
			
			receivedByte |= gpio_get_level(MISOPIN); // Read and store into byte
			
			gpio_set_level(SCLKPIN,0); // Wait on Falling
			usleep(10); // delay for clock
			
        }

        buffer[j] = receivedByte;  // Store the received byte in the buffer
    }
    
    gpio_set_level(CSPIN,1); // Deselect Slave
    gpio_set_level(SCLKPIN, 0); // Place clock in idle state
}
