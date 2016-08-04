/*
 * bootloader.c
 *
 * Created: 14.07.2016 14:51:22
 * Author : Viktor
 */ 

#define OLD_START 0x0000
#define OLD_END 0x0800
#define NEW_START 0x0800
#define NEW_END 0x1000

#define APPL_END_PAGE 0x07C0

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h> /* For exit() function */
#include "initialization.h"
#include "identificator.h"
#include "application.h"
#include "avr/wdt.h"

void __attribute__ ((naked)) move_interrupts_to_boot_section(void) __attribute__((section(".init3")));
void __attribute__ ((naked)) turn_off_watchdog(void) __attribute__((section(".init3")));
void __attribute__ ((naked)) move_interrupts_to_application_section(void) __attribute__((section(".fini8")));
void __attribute__ ((naked)) jump_to_0_address(void) __attribute__((section(".fini0")));


const version_typedef boot_ver __attribute__((__used__, __section__(".boot_end_page"))) = {"boot_ver", "0.1"};

uint8_t volatile i = 0;
uint8_t buf[SPM_PAGESIZE + 2];
uint8_t *data = buf + 2;

ISR(USART_RXC_vect)
{
	data[i++ & (SPM_PAGESIZE - 1)] = UDR;
}

int main(void)
{
	init_peripheral();
	
	copy_identificator_from_at24c32_to_sram(buf);
	
	switch (identificator_check((version_typedef *)data, (version_typedef *)APPL_END_PAGE))
	{
		case AT24C32_FAIL_ATMEGA8_FAIL:
			copy_from_uart_to_at24c32(NEW_START, NEW_END);
			wdt_enable(WDTO_15MS);
			while(1);
		
		case AT24C32_OK_ATMEGA8_OK:
			if (version_check((version_typedef *)data, (version_typedef *)APPL_END_PAGE) != NEWER)
				break;
			copy_from_flash_to_at24c32(OLD_START, OLD_END);
		
		case AT24C32_OK_ATMEGA8_FAIL:
			copy_from_at24c32_to_flash(NEW_START, NEW_END);
			break;
			
		default: break;
	}
	
	exit(0);
}

int main1(void)
{
	init_peripheral();
		
	copy_from_uart_to_at24c32(NEW_START, NEW_END);
	
	while(1);
}

void move_interrupts_to_boot_section(void)
{
	/* Enable change of interrupt vectors */
	GICR = _BV(IVCE);
	/* Move interrupts to boot flash section */
	GICR = _BV(IVSEL);
}

void move_interrupts_to_application_section(void)
{
	/* Enable change of interrupt vectors */
	GICR |= _BV(IVCE);
	/* Move interrupts to application section */
	GICR &= ~_BV(IVSEL);
}

void jump_to_0_address(void)
{
	__asm__ __volatile__	\
	(						\
	"clr  ZH\n\t"			\
	"clr  ZL\n\t"			\
	"ijmp\n\t"				\
	:						\
	:						\
	:						\
	);						\
}

void turn_off_watchdog(void)
{
	wdt_disable();
}
