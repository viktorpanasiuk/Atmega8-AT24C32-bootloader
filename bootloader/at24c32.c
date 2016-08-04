/*
 * at24c32.c
 *
 * Created: 15.07.2016 22:03:23
 *  Author: Viktor
 */ 

#include "AT24C32.h"
#include "i2c.h"

typedef struct {
	uint8_t lo;
	uint8_t hi;
} at24c32_mem_addr_typedef;

void at24c32_write(uint16_t address, uint8_t *buf, uint16_t n)
{
	i2c_struct i2c;
	
	at24c32_mem_addr_typedef *mem_addr = (at24c32_mem_addr_typedef *)&address;
	
	i2c.addr = AT24C32_ADDRESS;
	i2c.n_rd = 0;
	
	while (n)
	{
		uint8_t number_of_bytes_before_the_next_page = AT24C32_PAGESIZE - (address & (AT24C32_PAGESIZE - 1));
		
		uint8_t m = (n > number_of_bytes_before_the_next_page) ? number_of_bytes_before_the_next_page : n;
				
		buf[0] = mem_addr->hi;
		buf[1] = mem_addr->lo;
		
		i2c.data = buf;
		i2c.n_wr = m + 2;
		
		i2c_routine(&i2c);
		
		address += m;
		n -= m;
		buf += m;
	}
}

void at24c32_read(uint16_t address, uint8_t *buf, uint16_t n)
{
	i2c_struct i2c;
	
	at24c32_mem_addr_typedef *mem_addr = (at24c32_mem_addr_typedef *)&address;
	
	buf[0] = mem_addr->hi;
	buf[1] = mem_addr->lo;
	
	i2c.addr = AT24C32_ADDRESS;
	i2c.data = buf;
	i2c.n_wr = 2;
	i2c.n_rd = n;
	
	i2c_routine(&i2c);
}
