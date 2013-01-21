/** @defgroup STM32L1xx_adc_defines ADC Defines

@brief <b>Defined Constants and Types for the STM32L1xx Analog to Digital Converters</b>

@ingroup STM32L1xx_defines

@version 1.0.0

@author @htmlonly &copy; @endhtmlonly 2013 Karl Palsson <karlp@remake.is>

@date 18 August 2012

LGPL License Terms @ref lgpl_license
 */
/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2013 Karl Palsson <karlp@remake.is>
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

#ifndef LIBOPENCM3_ADC_H
#define LIBOPENCM3_ADC_H

#include <libopencm3/stm32/memorymap.h>
#include <libopencm3/stm32/common/adc_common_all.h>

/* ADC sample time register 3 (ADC_SMPR3) */
#define ADC_SMPR3(block)		MMIO32(block + 0x14)
#define ADC1_SMPR3			ADC_SMPR3(ADC1)

/* ADC injected channel data offset register x (ADC_JOFRx) (x=1..4) */
#define ADC_JOFR1(block)		MMIO32(block + 0x18)
#define ADC_JOFR2(block)		MMIO32(block + 0x1c)
#define ADC_JOFR3(block)		MMIO32(block + 0x20)
#define ADC_JOFR4(block)		MMIO32(block + 0x24)
#define ADC1_JOFR1			ADC_JOFR1(ADC1)
#define ADC1_JOFR2			ADC_JOFR2(ADC1)
#define ADC1_JOFR3			ADC_JOFR3(ADC1)
#define ADC1_JOFR4			ADC_JOFR4(ADC1)

/* ADC watchdog high threshold register (ADC_HTR) */
#define ADC_HTR(block)			MMIO32(block + 0x28)
#define ADC1_HTR			ADC_HTR(ADC1)

/* ADC watchdog low threshold register (ADC_LTR) */
#define ADC_LTR(block)			MMIO32(block + 0x2c)
#define ADC1_LTR			ADC_LTR(ADC1)

/* ADC regular sequence register 1 (ADC_SQR1) */
#define ADC_SQR1(block)			MMIO32(block + 0x30)
#define ADC1_SQR1			ADC_SQR1(ADC1)

/* ADC regular sequence register 2 (ADC_SQR2) */
#define ADC_SQR2(block)			MMIO32(block + 0x34)
#define ADC1_SQR2			ADC_SQR2(ADC1)

/* ADC regular sequence register 3 (ADC_SQR3) */
#define ADC_SQR3(block)			MMIO32(block + 0x38)
#define ADC1_SQR3			ADC_SQR3(ADC1)

/* ADC regular sequence register 4 (ADC_SQR4) */
#define ADC_SQR4(block)			MMIO32(block + 0x3c)
#define ADC1_SQR4			ADC_SQR4(ADC1)

/* ADC regular sequence register 5 (ADC_SQR5) */
#define ADC_SQR5(block)			MMIO32(block + 0x40)
#define ADC1_SQR5			ADC_SQR5(ADC1)

/* ADC injected sequence register (ADC_JSQR) */
#define ADC_JSQR(block)			MMIO32(block + 0x44)
#define ADC1_JSQR			ADC_JSQR(ADC1)

/* ADC injected data register x (ADC_JDRx) (x=1..4) */
#define ADC_JDR1(block)			MMIO32(block + 0x48)
#define ADC_JDR2(block)			MMIO32(block + 0x4c)
#define ADC_JDR3(block)			MMIO32(block + 0x50)
#define ADC_JDR4(block)			MMIO32(block + 0x54)
#define ADC1_JDR1			ADC_JDR1(ADC1)
#define ADC1_JDR2			ADC_JDR2(ADC1)
#define ADC1_JDR3			ADC_JDR3(ADC1)
#define ADC1_JDR4			ADC_JDR4(ADC1)

/* ADC regular data register (ADC_DR) */
#define ADC_DR(block)			MMIO32(block + 0x58)
#define ADC1_DR				ADC_DR(ADC1)

/* ADC sample time register 0 (ADC_SMPR0) (high/med+ only) */
#define ADC_SMPR0(block)		MMIO32(block + 0x5c)
#define ADC1_SMPR0			ADC_SMPR0(ADC1)

#define ADC_CSR				MMIO32(ADC1 + 0x300)
#define ADC_CCR				MMIO32(ADC1 + 0x304)


/* --- ADC_SR values ------------------------------------------------------- */
#define ADC_SR_JCNR			(1 << 9)
#define ADC_SR_RCNR			(1 << 8)
#define ADC_SR_ADONS			(1 << 6)
#define ADC_SR_OVR			(1 << 5)

/* --- ADC_CR1 values ------------------------------------------------------- */
#define ADC_CR1_OVRIE			(1 << 28)
/****************************************************************************/
/** @defgroup adc_cr1_res ADC Resolution.
@ingroup STM32L1xx_adc_defines
@{*/
#define ADC_CR1_RES_12_BIT		0
#define ADC_CR1_RES_10_BIT		1
#define ADC_CR1_RES_8_BIT		2
#define ADC_CR1_RES_6_BIT		3
/**@}*/
#define ADC_CR1_RES_MASK		(0x3)
#define ADC_CR1_RES_SHIFT		24
#define ADC_CR1_PDI			(1 << 17)
#define ADC_CR1_PDD			(1 << 16)


/* --- ADC_CR2 values ------------------------------------------------------- */
/* SWSTART: */ /** Start conversion of regular channels. */
#define ADC_CR2_SWSTART			(1 << 30)
#define ADC_CR2_EXTEN_DISABLED		0
#define ADC_CR2_EXTEN_RISING		1
#define ADC_CR2_EXTEN_FALLING		2
#define ADC_CR2_EXTEN_BOTH		3
#define ADC_CR2_EXTEN_SHIFT		28
#define ADC_CR2_EXTEN_MASK		0x3

// FIXME - add the values here
#define ADC_CR2_EXTSEL_SHIFT		24
#define ADC_CR2_EXTSEL_MASK		0xf

#define ADC_CR2_JSWSTART		(1 << 22)
#define ADC_CR2_JEXTEN_DISABLED		0
#define ADC_CR2_JEXTEN_RISING		1
#define ADC_CR2_JEXTEN_FALLING		2
#define ADC_CR2_JEXTEN_BOTH		3
#define ADC_CR2_JEXTEN_SHIFT		20
#define ADC_CR2_JEXTEN_MASK		0x3
// FIXME - add the values here
#define ADC_CR2_JEXTSEL_SHIFT		16
#define ADC_CR2_JEXTSEL_MASK		0xf

#define ADC_CR2_EOCS			(1 << 10)
#define ADC_CR2_DDS			(1 << 9)
// FIXME- add the values here
#define ADC_CR2_DELS_SHIFT		4
#define ADC_CR2_DELS_MASK		0x7

#define ADC_CR2_ADC_CFG			(1 << 2)




/* --- ADC_SMPRx generic values -------------------------------------------- */
/****************************************************************************/
/* ADC_SMPRG ADC Sample Time Selection for Channels */
/** @defgroup adc_sample_rg ADC Sample Time Selection for All Channels
@ingroup STM32L1xx_adc_defines

@{*/
#define ADC_SMPR_SMP_4CYC		0x0
#define ADC_SMPR_SMP_9CYC		0x1
#define ADC_SMPR_SMP_16CYC		0x2
#define ADC_SMPR_SMP_24CYC		0x3
#define ADC_SMPR_SMP_48CYC		0x4
#define ADC_SMPR_SMP_96CYC		0x5
#define ADC_SMPR_SMP_192CYC		0x6
#define ADC_SMPR_SMP_384CYC		0x7
/**@}*/

#define ADC_SQR_MASK			0x1f

#define ADC_CCR_TSVREFE			(1 << 23)

#endif
