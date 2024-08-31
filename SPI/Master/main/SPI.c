/*
 * SPI.c (master)
 *
 *  Created on: Aug 25, 2024
 *      Author: Joel
 */

#include "SPI.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include <sys/unistd.h>
#include <unistd.h>

void INITSPI(void) {
	
    gpio_set_direction(SCLKPIN, GPIO_MODE_OUTPUT);
    
    gpio_set_direction(MOSIPIN, GPIO_MODE_OUTPUT);
    
    gpio_set_direction(MISOPIN, GPIO_MODE_INPUT);
    
    gpio_set_direction(CSPIN, GPIO_MODE_OUTPUT);
    
    gpio_set_level(CSPIN, 1);
    
    gpio_set_level(SCLKPIN, 0);
    
    gpio_set_level(SCLKPIN, 1);
    
}

void WRITEBYTE(uint8_t byte) {
	
	gpio_set_level(CSPIN, 0);  // Select the slave
	
    for (uint8_t i = 0; i < 8; i++) {
		
        gpio_set_level(MOSIPIN, (byte & 0x80) ? 1 : 0);  // Set MOSI to corresponding bit
        
        gpio_set_level(SCLKPIN, 1);  // Clock high (active edge)
        
        while (gpio_get_level(MISOPIN) == 0) {}
        
        //usleep(100);  // Small delay to allow the slave to read
        
        byte <<= 1;  // Shift to the next bit
        
        gpio_set_level(SCLKPIN, 0);  // Clock low (idle edge)
        
        while (gpio_get_level(MISOPIN) == 1) {}
        
    }
    
    gpio_set_level(CSPIN, 1); // Deselect the slave
    
}

void TRANSMIT(uint8_t *data, uint32_t length) {
	
    for (int i = 0; i < length; i++) {
		
        WRITEBYTE(*data);
        data++; 
    }
    
}
uint8_t READBYTE(void) {
    uint8_t readByte = 0;

    gpio_set_level(CSPIN, 0);  // Select the slave
    
    for (uint8_t i = 0; i < 8; i++) {
        gpio_set_level(SCLKPIN, 1);  // Clock high (active edge)
        
        readByte <<= 1;  // Shift to make room for the next bit
        readByte |= gpio_get_level(MISOPIN);  // Read the bit from MISO
        
        gpio_set_level(SCLKPIN, 0);  // Clock low (idle edge)
    }
    
    gpio_set_level(CSPIN, 1);  // Deselect the slave
    
    return readByte;
}


