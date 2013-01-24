/** @defgroup STM32L1xx-flash-file Flash

@ingroup STM32L1xx

@brief <b>libopencm3 STM32L1xx Flash/EEPROM Control</b>

@version 1.0.0

@author @htmlonly &copy; @endhtmlonly 2012-13 Karl Palsson <karlp@tweak.net.au>

@date January 2013

This library supports the flash & eeprom subsystem for the
STM32L1 series of ARM Cortex Microcontrollers by ST Microelectronics.

LGPL License Terms @ref lgpl_license
 */
/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2010 Thomas Otto <tommi@viadmin.org>
 * Copyright (C) 2010 Mark Butler <mbutler@physics.otago.ac.nz>
 * Copyright (C) 2012-13 Karl Palsson <karlp@tweak.net.au>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/l1/flash.h>

void flash_64bit_enable(void)
{
	FLASH_ACR |= FLASH_ACC64;
}

void flash_64bit_disable(void)
{
	FLASH_ACR &= ~FLASH_ACC64;
}

void flash_prefetch_enable(void)
{
	FLASH_ACR |= FLASH_PRFTEN;
}

void flash_prefetch_disable(void)
{
	FLASH_ACR &= ~FLASH_PRFTEN;
}

void flash_set_ws(u32 ws)
{
	u32 reg32;

	reg32 = FLASH_ACR;
	reg32 &= ~(1 << 0);
	reg32 |= ws;
	FLASH_ACR = reg32;
}

void flash_unlock_pecr(void)
{
	FLASH_PEKEYR = FLASH_PEKEY1;
	FLASH_PEKEYR = FLASH_PEKEY2;
}

void flash_lock_pecr(void)
{
	FLASH_PECR |= FLASH_PELOCK;
}

void flash_unlock_progmem(void)
{
	flash_unlock_pecr();
	FLASH_PRGKEYR = FLASH_PRGKEY1;
	FLASH_PRGKEYR = FLASH_PRGKEY2;
}

void flash_lock_progmem(void)
{
	FLASH_PECR |= FLASH_PRGLOCK;
}

void flash_unlock_optbytes(void)
{
	flash_unlock_pecr();
	FLASH_OPTKEYR = FLASH_OPTKEY1;
	FLASH_OPTKEYR = FLASH_OPTKEY2;
}

void flash_lock_optbytes(void)
{
	FLASH_PECR |= FLASH_OPTLOCK;
}

void flash_unlock(u32 bits)
{
	flash_unlock_pecr();
	if (bits & FLASH_LOCKS_EEPROM) {
		; // nothing else to do
	}
	if (bits & FLASH_LOCKS_PROGMEM) {
		flash_unlock_progmem();
	}
	if (bits & FLASH_LOCKS_OPTBYTES) {
		flash_unlock_optbytes();
	}
}

void flash_lock()
{
	flash_lock_optbytes();
	flash_lock_progmem();
	flash_lock_pecr();
}

/** @brief Write a word to eeprom

Writes a data word to EEPROM at the requested address, erasing if necessary, 
and locking afterwards.

@param[in] address must point to EEPROM space, no checking!
@param[in] data word to write
 */
void eeprom_program_word(u32 address, u32 data)
{
	flash_unlock_pecr();
	/* erase only if needed */
	FLASH_PECR &= ~FLASH_FTDW;
	MMIO32(address) = data;
	flash_lock_pecr();
}

/** @brief Write a word to eeprom

Writes a block of words to EEPROM at the requested address, erasing if necessary, 
and locking afterwards.  Only wordwise writing is safe for writing any value

@param[in] address must point to EEPROM space, no checking!
@param[in] data pointer to data to write
@param[in] length size of of data in WORDS!
 */
void eeprom_program_words(u32 address, u32 *data, int length_in_words)
{
	int i;
	flash_unlock_pecr();
	while (FLASH_SR & FLASH_BSY);
	/* erase only if needed */
	FLASH_PECR &= ~FLASH_FTDW;
	for (i = 0; i < length_in_words; i++) {
		MMIO32(address + (i * sizeof(u32))) = *(data+i);
		while (FLASH_SR & FLASH_BSY);
	}
	flash_lock_pecr();
}