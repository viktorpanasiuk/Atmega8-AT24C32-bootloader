/*
 * i2c.c
 *
 * Created: 15.07.2016 22:02:10
 *  Author: Viktor
 */ 

#include "i2c.h"
#include <util/twi.h>

uint8_t i2c_routine(i2c_struct *i2c)
{	
	uint8_t status = 0;
	
	while(1)
	{
		switch(TWSR)
		{
			case TW_NO_INFO:
			case TW_MT_SLA_NACK:
			case TW_MR_SLA_NACK:
				TWCR = _BV(TWINT)|_BV(TWEN)|_BV(TWSTA);
				break;
				
			case TW_START:
			case TW_REP_START:
				TWDR = (i2c->n_wr) ? i2c->addr|TW_WRITE : i2c->addr|TW_READ;
				TWCR = _BV(TWINT)|_BV(TWEN);
				break;
			
			case TW_MT_SLA_ACK:
			case TW_MT_DATA_ACK:
				if (i2c->n_wr)
				{
					i2c->n_wr--;
					TWDR = *i2c->data++;
					TWCR = _BV(TWINT)|_BV(TWEN);
				}
				else if (!i2c->n_rd)
					status = TWSR;
				else
					TWCR = _BV(TWINT)|_BV(TWEN)|_BV(TWSTA);
				break;
				
			case TW_MR_DATA_NACK:
				status = TWSR;
				
			case TW_MR_DATA_ACK:
				*i2c->data++ = TWDR;
				if (status) break;
				
			case TW_MR_SLA_ACK:
				TWCR = (--i2c->n_rd) ? _BV(TWINT)|_BV(TWEN)|_BV(TWEA) : _BV(TWINT)|_BV(TWEN);
				break;
				
			default:
				status = TWSR;
		}
		if (status) break;
		while (!(TWCR & (1<<TWINT)));
	}
	TWCR = _BV(TWINT)|_BV(TWEN)|_BV(TWSTO);
	while ((TWCR & (1<<TWSTO)));
	
	return status;
}
