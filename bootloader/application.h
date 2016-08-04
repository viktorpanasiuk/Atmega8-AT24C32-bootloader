/*
 * application.h
 *
 * Created: 25.07.2016 17:10:07
 *  Author: Viktor
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <avr/io.h>

void copy_from_flash_to_at24c32(uint16_t from, uint16_t to);
void copy_from_at24c32_to_flash(uint16_t from, uint16_t to);
void copy_from_at24c32_to_uart(uint16_t from, uint16_t to);
void copy_from_uart_to_at24c32(uint16_t from, uint16_t to);
void copy_from_flash_to_uart(uint16_t from, uint16_t to);
void copy_identificator_from_at24c32_to_sram(uint8_t *buf);

#endif /* APPLICATION_H_ */