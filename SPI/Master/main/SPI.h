/*
 * SPI.h
 *
 *  Created on: Aug 25, 2024
 *      Author: Joel
 */

#ifndef MAIN_SPI_H_
#define MAIN_SPI_H_

#include "driver/gpio.h"

#define MOSIPIN 23
#define MISOPIN 19
#define SCLKPIN 18
#define CSPIN 5

void INITSPI(void);
void MASTERTRANSMIT(uint8_t* data, uint32_t length);
void MASTERRECEIVE(uint8_t *buffer, uint32_t length);

#endif /* MAIN_SPI_H_ */
