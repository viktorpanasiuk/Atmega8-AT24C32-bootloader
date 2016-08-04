/*
 * identificator.h
 *
 * Created: 30.07.2016 14:54:30
 *  Author: Viktor
 */ 


#ifndef IDENTIFICATOR_H_
#define IDENTIFICATOR_H_

#include <avr/io.h>

#define IDENTIFICATOR_LENGTH	32 /* Length of identificator string */
#define VERSION_LENGTH			32 /* Length of version string */

#define AT24C32_CHECK_FAIL	(0 << 0) /* AT24C32 has no firmware */
#define AT24C32_CHECK_OK	(1 << 0) /* AT24C32 has firmware */
#define ATMEGA8_CHECK_FAIL	(0 << 0) /* ATmega8 has no firmware */
#define ATMEGA8_CHECK_OK	(1 << 1) /* ATmega8 has firmware */

typedef enum {
	AT24C32_FAIL_ATMEGA8_FAIL	= AT24C32_CHECK_FAIL | ATMEGA8_CHECK_FAIL, /* Neither AT24C32 no ATmega8 has no firmware */
	AT24C32_FAIL_ATMEGA8_OK		= AT24C32_CHECK_FAIL | ATMEGA8_CHECK_OK, /* AT24C32 has firmware but ATmega8 has not */
	AT24C32_OK_ATMEGA8_FAIL		= AT24C32_CHECK_OK | ATMEGA8_CHECK_FAIL, /* AT24C32 has no firmware but ATmega8 has */
	AT24C32_OK_ATMEGA8_OK		= AT24C32_CHECK_OK | ATMEGA8_CHECK_OK /* Both AT24C32 and ATmega8 has firmware */
} identificator_check_typedef;

typedef enum {
	OLDER, /* AT24C32's firmware is older than ATmega8's */
	EQUAL, /* AT24C32's firmware the same as ATmega8's */
	NEWER /* AT24C32's firmware is newer than ATmega8's */
} version_check_typedef;

typedef struct {
	char identificator[IDENTIFICATOR_LENGTH]; /* String for identificator of IDENTIFICATION LENGTH length */
	char version[VERSION_LENGTH]; /* String for version of VERSION_LENGTH length */
} version_typedef;

/* This function provide the checking identification
	

*/
identificator_check_typedef identificator_check(const version_typedef *at24c32_id, const version_typedef *atmega8_id);
version_check_typedef version_check(const version_typedef *at24c32_id, const version_typedef *atmega8_id);

#endif /* IDENTIFICATOR_H_ */