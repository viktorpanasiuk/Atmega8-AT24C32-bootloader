/*
 * AT24C32.h
 *
 * Created: 15.07.2016 22:03:03
 *  Author: Viktor
 */ 


#ifndef AT24C32_H_
#define AT24C32_H_

#define AT24C32_ADDRESS 0xA0
#define AT24C32_PAGESIZE 32

#define IDENTIFICATOR_ADDRESS 0x0FC0

#include <avr/io.h>

typedef struct {
	uint8_t addr_hi;
	uint8_t addr_lo;
	uint8_t data[SPM_PAGESIZE];
} at24c32_buf_typedef;

void at24c32_write(uint16_t address, uint8_t *buf, uint16_t n);
void at24c32_read(uint16_t address, uint8_t *buf, uint16_t n);

#endif /* AT24C32_H_ */
