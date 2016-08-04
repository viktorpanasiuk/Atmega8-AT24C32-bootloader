/*
 * identificator.c
 *
 * Created: 30.07.2016 14:54:21
 *  Author: Viktor
 */ 

#include "identificator.h"
#include <avr/pgmspace.h>
#include <string.h>

identificator_check_typedef identificator_check(const version_typedef *at24c32_id, const version_typedef *atmega8_id)
{
	uint8_t status = AT24C32_FAIL_ATMEGA8_FAIL;
	const char gold_id[] = "appl_ver";
	
	status |= (strcmp	(gold_id,		 (char *)(at24c32_id->identificator))) ? AT24C32_CHECK_FAIL : AT24C32_CHECK_OK;
	status |= (strcmp_PF(gold_id, (uint_farptr_t)(atmega8_id->identificator))) ? ATMEGA8_CHECK_FAIL : ATMEGA8_CHECK_OK;
	
	return status;
}

version_check_typedef version_check(const version_typedef *at24c32_id, const version_typedef *atmega8_id)
{	
	int version = strcmp_PF((char *)(at24c32_id->version), (uint_farptr_t)(atmega8_id->version));
	
	return (version) ? ((version > 0) ? NEWER : OLDER) : EQUAL;
}