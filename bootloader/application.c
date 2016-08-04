/*
 * application.c
 *
 * Created: 25.07.2016 17:09:55
 *  Author: Viktor
 */ 

#include "application.h"
#include "at24c32.h"
#include "bootloader.h"
#include "uart.h"

extern uint8_t buf[];
extern uint8_t *data;

void copy_from_flash_to_at24c32(uint16_t from, uint16_t to)
{
	uint16_t addr_at24c32;
	uint16_t addr_atmega8;
	
	for (addr_at24c32 = from, addr_atmega8 = 0; addr_at24c32 < to; addr_atmega8 += AT24C32_PAGESIZE, addr_at24c32 += AT24C32_PAGESIZE)
	{
		copy_from_flash_to_sram(addr_atmega8, data);
		at24c32_write(addr_at24c32, buf, AT24C32_PAGESIZE);
	}
}

void copy_from_at24c32_to_flash(uint16_t from, uint16_t to)
{
	uint16_t addr_at24c32;
	uint16_t addr_atmega8;
	
	for (addr_at24c32 = from, addr_atmega8 = 0; addr_at24c32 < to; addr_at24c32 += SPM_PAGESIZE, addr_atmega8 += SPM_PAGESIZE)
	{
		at24c32_read(addr_at24c32, buf, SPM_PAGESIZE);
		copy_from_sram_to_flash(addr_atmega8, data);
	}
}

void copy_from_at24c32_to_uart(uint16_t from, uint16_t to)
{
	uint16_t addr_at24c32;
	
	for (addr_at24c32 = from; addr_at24c32 < to; addr_at24c32 += SPM_PAGESIZE)
	{
		at24c32_read(addr_at24c32, buf, SPM_PAGESIZE);
		copy_from_sram_to_uart(data, SPM_PAGESIZE);
	}
}

void copy_from_uart_to_at24c32(uint16_t from, uint16_t to)
{
	extern uint8_t volatile i;
	uint16_t addr_at24c32;
	uint8_t shift = 0;
	
	sei();
	for (addr_at24c32 = from; addr_at24c32 < to; addr_at24c32 += AT24C32_PAGESIZE, shift ^= AT24C32_PAGESIZE)
	{
		while ((i & AT24C32_PAGESIZE) == shift);
		at24c32_write(addr_at24c32, buf + shift, AT24C32_PAGESIZE);
	}
	cli();
}

void copy_from_flash_to_uart(uint16_t from, uint16_t to)
{
	uint16_t addr_atmega8;
	
	for (addr_atmega8 = from; addr_atmega8 < to; addr_atmega8 += AT24C32_PAGESIZE)
	{		
		copy_from_flash_to_sram(addr_atmega8, data);
		copy_from_sram_to_uart(data, AT24C32_PAGESIZE);
	}
}

void copy_identificator_from_at24c32_to_sram(uint8_t *buf)
{
	at24c32_read(IDENTIFICATOR_ADDRESS, buf, SPM_PAGESIZE);
}