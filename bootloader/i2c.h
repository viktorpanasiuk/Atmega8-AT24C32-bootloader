/*
 * i2c.h
 *
 * Created: 15.07.2016 22:02:20
 *  Author: Viktor
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

typedef struct
{
	uint8_t addr;
	uint8_t *data;
	uint8_t n_wr;
	uint8_t n_rd;
} i2c_struct;

uint8_t i2c_routine(i2c_struct *i2c);

#endif /* I2C_H_ */