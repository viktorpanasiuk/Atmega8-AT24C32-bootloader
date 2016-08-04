/*
 * application.c
 *
 * Created: 02.08.2016 22:52:37
 * Author : Viktor
 */ 

#define F_CPU 16000000UL

#define IDENTIFICATOR_LENGTH	32 /* Length of identificator string */
#define VERSION_LENGTH			32 /* Length of version string */

#include <avr/io.h>
#include <util/delay.h>

typedef struct {
	char identificator[IDENTIFICATOR_LENGTH]; /* String for identificator of IDENTIFICATION LENGTH length */
	char version[VERSION_LENGTH]; /* String for version of VERSION_LENGTH length */
} version_typedef;

const version_typedef appl_ver __attribute__((__used__, __section__(".appl_end_page"))) = {"appl_ver", "0.1"};

int main(void)
{
	DDRB |= _BV(DDB0);
		
    /* Replace with your application code */
    while (1) 
    {
		PORTB ^= _BV(PB0);
		_delay_ms(1000);
    }
}