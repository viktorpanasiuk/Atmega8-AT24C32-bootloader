/*
 * uart.c
 *
 * Created: 25.07.2016 18:33:35
 *  Author: Viktor
 */ 

#include "uart.h"

void copy_from_sram_to_uart(uint8_t *buf, uint8_t n)
{
	while(n--)
	{
		while (!(UCSRA & (1<<UDRE)));
		UDR = *buf++;
	}
}