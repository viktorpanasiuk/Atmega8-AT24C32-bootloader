/*
 * bootloader.h
 *
 * Created: 14.07.2016 18:20:40
 *  Author: Viktor
 */ 


#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

#include <avr/boot.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "at24c32.h"

void copy_from_sram_to_flash(uint16_t address, uint8_t *buf);

void copy_from_flash_to_sram(uint16_t address, uint8_t *buf);

#endif /* BOOTLOADER_H_ */