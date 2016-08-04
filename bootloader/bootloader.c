/*
 * bootloader.c
 *
 * Created: 14.07.2016 18:21:32
 *  Author: Viktor
 */ 

#include "bootloader.h"
#include "AT24C32.h"

void copy_from_sram_to_flash(uint16_t address, uint8_t *buf)
{
	uint16_t i;
	uint8_t sreg;

	// Disable interrupts.

	sreg = SREG;
	cli();
	
	eeprom_busy_wait ();

	boot_page_erase (address);
	boot_spm_busy_wait ();      // Wait until the memory is erased.

	for (i=0; i<SPM_PAGESIZE; i+=2)
	{
		// Set up little-endian word.

		uint16_t w;
		
		w = *buf++;
		w += (*buf++) << 8;
		
		boot_page_fill (address + i, w);
	}

	boot_page_write (address);     // Store buffer in flash page.
	boot_spm_busy_wait();       // Wait until the memory is written.

	// Reenable RWW-section again. We need this if we want to jump back
	// to the application after bootloading.

	boot_rww_enable ();

	// Re-enable interrupts (if they were ever enabled).

	SREG = sreg;
}

void copy_from_flash_to_sram(uint16_t address, uint8_t *buf)
{
	uint8_t n = AT24C32_PAGESIZE;
	
	while (n--)
		*buf++ = pgm_read_byte(address++);
}

