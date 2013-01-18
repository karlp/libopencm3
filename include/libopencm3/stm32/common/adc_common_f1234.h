/** @addtogroup adc_defines */
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

/* THIS FILE SHOULD NOT BE INCLUDED DIRECTLY, BUT ONLY VIA ADC.H */

#ifndef LIBOPENCM3_ADC_COMMON_F1234_H
#define LIBOPENCM3_ADC_COMMON_F1234_H

#include <libopencm3/stm32/common/adc_common_all.h>

/* --- Convenience macros -------------------------------------------------- */

#define ADC2				ADC2_BASE
#define ADC3				ADC3_BASE

/* --- ADC registers ------------------------------------------------------- */

/* ADC status register (ADC_SR) */
#define ADC2_SR				ADC_SR(ADC2)
#define ADC3_SR				ADC_SR(ADC3)

/* ADC control register 1 (ADC_CR1) */
#define ADC2_CR1			ADC_CR1(ADC2)
#define ADC3_CR1			ADC_CR1(ADC3)

/* ADC control register 2 (ADC_CR2) */
#define ADC2_CR2			ADC_CR2(ADC2)
#define ADC3_CR2			ADC_CR2(ADC3)

/* ADC sample time register 1 (ADC_SMPR1) */
#define ADC2_SMPR1			ADC_SMPR1(ADC2)
#define ADC3_SMPR1			ADC_SMPR1(ADC3)

/* ADC sample time register 2 (ADC_SMPR2) */
#define ADC2_SMPR2			ADC_SMPR2(ADC2)
#define ADC3_SMPR2			ADC_SMPR2(ADC3)

/* ADC injected channel data offset register x (ADC_JOFRx) (x=1..4) */
#define ADC2_JOFR1			ADC_JOFR1(ADC2)
#define ADC3_JOFR1			ADC_JOFR1(ADC3)
#define ADC2_JOFR2			ADC_JOFR2(ADC2)
#define ADC3_JOFR2			ADC_JOFR2(ADC3)
#define ADC2_JOFR3			ADC_JOFR3(ADC2)
#define ADC3_JOFR3			ADC_JOFR3(ADC3)
#define ADC2_JOFR4			ADC_JOFR4(ADC2)
#define ADC3_JOFR4			ADC_JOFR4(ADC3)

/* ADC watchdog high threshold register (ADC_HTR) */
#define ADC2_HTR			ADC_HTR(ADC2)
#define ADC3_HTR			ADC_HTR(ADC3)

/* ADC watchdog low threshold register (ADC_LTR) */
#define ADC2_LTR			ADC_LTR(ADC2_BASE)
#define ADC3_LTR			ADC_LTR(ADC3_BASE)

/* ADC regular sequence register 1 (ADC_SQR1) */
#define ADC2_SQR1			ADC_SQR1(ADC2)
#define ADC3_SQR1			ADC_SQR1(ADC3)

/* ADC regular sequence register 2 (ADC_SQR2) */
#define ADC2_SQR2			ADC_SQR2(ADC2)
#define ADC3_SQR2			ADC_SQR2(ADC3)

/* ADC regular sequence register 3 (ADC_SQR3) */
#define ADC2_SQR3			ADC_SQR3(ADC2)
#define ADC3_SQR3			ADC_SQR3(ADC3)

/* ADC injected sequence register (ADC_JSQR) */
#define ADC2_JSQR			ADC_JSQR(ADC2_BASE)
#define ADC3_JSQR			ADC_JSQR(ADC3_BASE)

/* ADC injected data register x (ADC_JDRx) (x=1..4) */
#define ADC2_JDR1			ADC_JDR1(ADC2)
#define ADC3_JDR1			ADC_JDR1(ADC3)
#define ADC2_JDR2			ADC_JDR2(ADC2)
#define ADC3_JDR2			ADC_JDR2(ADC3)
#define ADC2_JDR3			ADC_JDR3(ADC2)
#define ADC3_JDR3			ADC_JDR3(ADC3)
#define ADC2_JDR4			ADC_JDR4(ADC2)
#define ADC3_JDR4			ADC_JDR4(ADC3)

/* ADC regular data register (ADC_DR) */
#define ADC2_DR				ADC_DR(ADC2)
#define ADC3_DR				ADC_DR(ADC3)

#endif
/**@}*/
