/*
 * SPI.c (slave)
 *
 *  Created on: Aug 25, 2024
 *      Author: Joel
 */

#include "SPI.h"
#include <stdint.h>

void INITSPI(void) {
    gpio_set_direction(SCLKPIN, GPIO_MODE_INPUT);  // Slave reads the clock signal
    
    gpio_set_direction(MOSIPIN, GPIO_MODE_INPUT);  // Slave reads the MOSI
    
    gpio_set_direction(MISOPIN, GPIO_MODE_OUTPUT);  // Slave would not use MISO in this case
    
    gpio_set_direction(CSPIN, GPIO_MODE_INPUT);    // Slave reads the chip select signal
    
}

uint8_t READBYTE(void) {
    uint8_t readByte = 0;
    
    while (gpio_get_level(CSPIN) == 1) {}  // Wait for Select
    

    for (uint8_t i = 0; i < 8; i++) {
		
        while (gpio_get_level(SCLKPIN) == 0) {}  // Wait for clock high
        
        readByte <<= 1;
        
        readByte |= gpio_get_level(MOSIPIN);  // Read MOSI bit
        
        gpio_set_level(MISOPIN, 1);
        
        while (gpio_get_level(SCLKPIN) != 0) {}  // Wait for clock low
        
        gpio_set_level(MISOPIN, 0);
        
    }

    return readByte;
}

void WRITEBYTE(uint8_t byte) {
    while (gpio_get_level(CSPIN) == 1) {}  // Wait for the master to select the slave
    
    for (uint8_t i = 0; i < 8; i++) {
        while (gpio_get_level(SCLKPIN) == 0) {}  // Wait for clock high
        
        gpio_set_level(MISOPIN, (byte & 0x80) ? 1 : 0);  // Set MISO to the corresponding bit
        byte <<= 1;  // Shift to the next bit
        
        while (gpio_get_level(SCLKPIN) == 1) {}  // Wait for clock low
    }
}


void TRANSMIT(uint8_t *data, uint32_t length){
	for(int i = 0; i < length; i++){
		WRITEBYTE(*data);
		data++;
	}
}