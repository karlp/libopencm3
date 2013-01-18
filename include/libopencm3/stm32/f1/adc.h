/** @defgroup STM32F1xx_adc_defines ADC Defines

@brief <b>Defined Constants and Types for the STM32F1xx Analog to Digital Converters</b>

@ingroup STM32F1xx_defines

@version 1.0.0

@author @htmlonly &copy; @endhtmlonly 2009 Edward Cheeseman <evbuilder@users.sourceforge.net>

@date 18 August 2012

LGPL License Terms @ref lgpl_license
 */
/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Edward Cheeseman <evbuilder@users.sourceforge.net>
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
#include <libopencm3/stm32/common/adc_common_f1234.h>


/* --- ADC_CR2 values ------------------------------------------------------ */

/* TSVREFE: */ /** Temperature sensor and V_REFINT enable. (ADC1 only!) */
#define ADC_CR2_TSVREFE			(1 << 23)

/* SWSTART: */ /** Start conversion of regular channels. */
#define ADC_CR2_SWSTART			(1 << 22)

/* JSWSTART: */ /** Start conversion of injected channels. */
#define ADC_CR2_JSWSTART		(1 << 21)

/* EXTTRIG: */ /** External trigger conversion mode for regular channels. */
#define ADC_CR2_EXTTRIG			(1 << 20)

/* EXTSEL[2:0]: External event select for regular group. */
/* The following are only valid for ADC1 and ADC2. */
/****************************************************************************/
/* ADC_CR2 EXTSEL[2:0] ADC Trigger Identifier for ADC1 and ADC2 */
/** @defgroup adc_trigger_regular_12 ADC Trigger Identifier for ADC1 and ADC2
@ingroup STM32F1xx_adc_defines

@{*/
/** Timer 1 Compare Output 1 */
#define ADC_CR2_EXTSEL_TIM1_CC1		(0x0 << 17)
/** Timer 1 Compare Output 2 */
#define ADC_CR2_EXTSEL_TIM1_CC2		(0x1 << 17)
/** Timer 1 Compare Output 3 */
#define ADC_CR2_EXTSEL_TIM1_CC3		(0x2 << 17)
/** Timer 2 Compare Output 2 */
#define ADC_CR2_EXTSEL_TIM2_CC2		(0x3 << 17)
/** Timer 3 Trigger Output */
#define ADC_CR2_EXTSEL_TIM3_TRGO	(0x4 << 17)
/** Timer 4 Compare Output 4 */
#define ADC_CR2_EXTSEL_TIM4_CC4		(0x5 << 17)
/** External Interrupt 11 */
#define ADC_CR2_EXTSEL_EXTI11		(0x6 << 17)
/** Software Trigger */
#define ADC_CR2_EXTSEL_SWSTART		(0x7 << 17)
/**@}*/

/* The following are only valid for ADC3 */
/****************************************************************************/
/* ADC_CR2 EXTSEL[2:0] ADC Trigger Identifier for ADC3 */
/** @defgroup adc_trigger_regular_3 ADC Trigger Identifier for ADC3
@ingroup STM32F1xx_adc_defines

@{*/
/** Timer 2 Compare Output 1 */
#define ADC_CR2_EXTSEL_TIM3_CC1		(0x0 << 17)
/** Timer 2 Compare Output 3 */
#define ADC_CR2_EXTSEL_TIM2_CC3		(0x1 << 17)
/** Timer 1 Compare Output 3 */
#define ADC_CR2_EXTSEL_TIM1_CC3		(0x2 << 17)
/** Timer 8 Compare Output 1 */
#define ADC_CR2_EXTSEL_TIM8_CC1		(0x3 << 17)
/** Timer 8 Trigger Output */
#define ADC_CR2_EXTSEL_TIM8_TRGO	(0x4 << 17)
/** Timer 5 Compare Output 1 */
#define ADC_CR2_EXTSEL_TIM5_CC1		(0x5 << 17)
/** Timer 5 Compare Output 3 */
#define ADC_CR2_EXTSEL_TIM5_CC3		(0x6 << 17)
/**@}*/

#define ADC_CR2_EXTSEL_MASK		(0x7 << 17)
#define ADC_CR2_EXTSEL_SHIFT		17

/* Note: Bit 16 is reserved, must be kept at reset value. */

/* JEXTTRIG: External trigger conversion mode for injected channels. */
#define ADC_CR2_JEXTTRIG		(1 << 15)

/* JEXTSEL[2:0]: External event selection for injected group. */
/* The following are only valid for ADC1 and ADC2. */
/****************************************************************************/
/* ADC_CR2 JEXTSEL[2:0] ADC Injected Trigger Identifier for ADC1 and ADC2 */
/** @defgroup adc_trigger_injected_12 ADC Injected Trigger Identifier for ADC1 and ADC2
@ingroup STM32F1xx_adc_defines

@{*/
/** Timer 1 Trigger Output */
#define ADC_CR2_JEXTSEL_TIM1_TRGO	(0x0 << 12)
/** Timer 1 Compare Output 4 */
#define ADC_CR2_JEXTSEL_TIM1_CC4	(0x1 << 12)
/** Timer 2 Trigger Output */
#define ADC_CR2_JEXTSEL_TIM2_TRGO	(0x2 << 12)
/** Timer 2 Compare Output 1 */
#define ADC_CR2_JEXTSEL_TIM2_CC1	(0x3 << 12)
/** Timer 3 Compare Output 4 */
#define ADC_CR2_JEXTSEL_TIM3_CC4	(0x4 << 12)
/** Timer 4 Trigger Output */
#define ADC_CR2_JEXTSEL_TIM4_TRGO	(0x5 << 12)
/** External Interrupt 15 */
#define ADC_CR2_JEXTSEL_EXTI15		(0x6 << 12)
/** Injected Software Trigger */
#define ADC_CR2_JEXTSEL_JSWSTART	(0x7 << 12) /* Software start. */
/**@}*/

/* The following are the different meanings for ADC3 only. */
/****************************************************************************/
/* ADC_CR2 JEXTSEL[2:0] ADC Injected Trigger Identifier for ADC3 */
/** @defgroup adc_trigger_injected_3 ADC Injected Trigger Identifier for ADC3
@ingroup STM32F1xx_adc_defines

@{*/
/** Timer 1 Trigger Output */
#define ADC_CR2_JEXTSEL_TIM1_TRGO	(0x0 << 12)
/** Timer 1 Compare Output 4 */
#define ADC_CR2_JEXTSEL_TIM1_CC4	(0x1 << 12)
/** Timer 4 Compare Output 3 */
#define ADC_CR2_JEXTSEL_TIM4_CC3	(0x2 << 12)
/** Timer 8 Compare Output 2 */
#define ADC_CR2_JEXTSEL_TIM8_CC2	(0x3 << 12)
/** Timer 8 Compare Output 4 */
#define ADC_CR2_JEXTSEL_TIM8_CC4	(0x4 << 12)
/** Timer 5 Trigger Output */
#define ADC_CR2_JEXTSEL_TIM5_TRGO	(0x5 << 12)
/** Timer53 Compare Output 4 */
#define ADC_CR2_JEXTSEL_TIM5_CC4	(0x6 << 12)
/** Injected Software Trigger */
#define ADC_CR2_JEXTSEL_JSWSTART	(0x7 << 12) /* Software start. */
/**@}*/

#define ADC_CR2_JEXTSEL_MASK		(0x7 << 12)
#define ADC_CR2_JEXTSEL_SHIFT		12

#endif
