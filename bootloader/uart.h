/*
 * uart.h
 *
 * Created: 25.07.2016 18:33:26
 *  Author: Viktor
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void copy_from_sram_to_uart(uint8_t *buf, uint8_t n);

#endif /* UART_H_ */