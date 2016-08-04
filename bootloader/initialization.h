/*
 * initialization.h
 *
 * Created: 25.07.2016 17:23:50
 *  Author: Viktor
 */ 


#ifndef INITIALIZATION_H_
#define INITIALIZATION_H_

#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

static void init_i2c(void)
{
	TWBR = 72; // 100kHz@16MHz
}

static void init_uart(unsigned int ubrr)
{
	/* Set baud rate */
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)(ubrr);
	/*UBRRH = 0;
	UBRRL = 0;*/
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 0stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}

static void init_peripheral(void)
{
	init_i2c();
	init_uart(MYUBRR);
}

#endif /* INITIALIZATION_H_ */