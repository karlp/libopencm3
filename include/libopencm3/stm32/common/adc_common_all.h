/** @addtogroup crc_defines */

/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2010 Thomas Otto <tommi@viadmin.org>
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

#ifndef LIBOPENCM3_ADC_COMMON_ALL_H
#define LIBOPENCM3_ADC_COMMON_ALL_H

#include <libopencm3/stm32/memorymap.h>
#include <libopencm3/cm3/common.h>

/* --- Convenience macros -------------------------------------------------- */

/* ADC port base addresses (for convenience) */
/****************************************************************************/
/** @defgroup adc_reg_base ADC register base addresses
@ingroup STM32F1xx_adc_defines

@{*/
#define ADC1				ADC1_BASE
/**@}*/

/* --- ADC registers ------------------------------------------------------- */

/* ADC status register (ADC_SR) */
#define ADC_SR(block)			MMIO32(block + 0x00)
#define ADC1_SR				ADC_SR(ADC1)

/* ADC control register 1 (ADC_CR1) */
#define ADC_CR1(block)			MMIO32(block + 0x04)
#define ADC1_CR1			ADC_CR1(ADC1)

/* ADC control register 2 (ADC_CR2) */
#define ADC_CR2(block)			MMIO32(block + 0x08)
#define ADC1_CR2			ADC_CR2(ADC1)

/* ADC sample time register 1 (ADC_SMPR1) */
#define ADC_SMPR1(block)		MMIO32(block + 0x0c)
#define ADC1_SMPR1			ADC_SMPR1(ADC1)

/* ADC sample time register 2 (ADC_SMPR2) */
#define ADC_SMPR2(block)		MMIO32(block + 0x10)
#define ADC1_SMPR2			ADC_SMPR2(ADC1)


/* --- ADC Channels ------------------------------------------------------- */

/****************************************************************************/
/** @defgroup adc_channel ADC Channel Numbers
@ingroup STM32F1xx_adc_defines

@{*/
#define ADC_CHANNEL0		0x00
#define ADC_CHANNEL1		0x01
#define ADC_CHANNEL2		0x02
#define ADC_CHANNEL3		0x03
#define ADC_CHANNEL4		0x04
#define ADC_CHANNEL5		0x05
#define ADC_CHANNEL6		0x06
#define ADC_CHANNEL7		0x07
#define ADC_CHANNEL8		0x08
#define ADC_CHANNEL9		0x09
#define ADC_CHANNEL10		0x0A
#define ADC_CHANNEL11		0x0B
#define ADC_CHANNEL12		0x0C
#define ADC_CHANNEL13		0x0D
#define ADC_CHANNEL14		0x0E
#define ADC_CHANNEL15		0x0F
#define ADC_CHANNEL16		0x10
#define ADC_CHANNEL17		0x11
#define ADC_CHANNEL18		0x11
#define ADC_CHANNEL_TEMP	ADC_CHANNEL16
#define ADC_CHANNEL_VREFINT	ADC_CHANNEL17
#define ADC_CHANNEL_VBAT	ADC_CHANNEL18
// TODO - L1 goes up to 31 here.
/**@}*/
#define ADC_MASK		    0x1F
#define ADC_SHIFT		    0

/* --- ADC_SR values ------------------------------------------------------- */

#define ADC_SR_STRT			(1 << 4)
#define ADC_SR_JSTRT			(1 << 3)
#define ADC_SR_JEOC			(1 << 2)
#define ADC_SR_EOC			(1 << 1)
#define ADC_SR_AWD			(1 << 0)

/* --- ADC_CR1 values ------------------------------------------------------ */

/* AWDEN: Analog watchdog enable on regular channels */
#define ADC_CR1_AWDEN			(1 << 23)

/* JAWDEN: Analog watchdog enable on injected channels */
#define ADC_CR1_JAWDEN			(1 << 22)

/* Note: Bits [21:20] are reserved, and must be kept at reset value. */


/* DISCNUM[2:0]: Discontinuous mode channel count. */
/****************************************************************************/
/** @defgroup adc_cr1_discnum ADC Number of channels in discontinuous mode.
@ingroup STM32F1xx_adc_defines

@{*/
#define ADC_CR1_DISCNUM_1CHANNELS       (0x0 << 13)
#define ADC_CR1_DISCNUM_2CHANNELS       (0x1 << 13)
#define ADC_CR1_DISCNUM_3CHANNELS       (0x2 << 13)
#define ADC_CR1_DISCNUM_4CHANNELS       (0x3 << 13)
#define ADC_CR1_DISCNUM_5CHANNELS       (0x4 << 13)
#define ADC_CR1_DISCNUM_6CHANNELS       (0x5 << 13)
#define ADC_CR1_DISCNUM_7CHANNELS       (0x6 << 13)
#define ADC_CR1_DISCNUM_8CHANNELS       (0x7 << 13)
/**@}*/
#define ADC_CR1_DISCNUM_MASK		(0x7 << 13)
#define ADC_CR1_DISCNUM_SHIFT		13

/* JDISCEN: */ /** Discontinuous mode on injected channels. */
#define ADC_CR1_JDISCEN			(1 << 12)

/* DISCEN: */ /** Discontinuous mode on regular channels. */
#define ADC_CR1_DISCEN			(1 << 11)

/* JAUTO: */ /** Automatic Injection Group conversion. */
#define ADC_CR1_JAUTO			(1 << 10)

/* AWDSGL: */ /** Enable the watchdog on a single channel in scan mode. */
#define ADC_CR1_AWDSGL			(1 << 9)

/* SCAN: */ /** Scan mode. */
#define ADC_CR1_SCAN			(1 << 8)

/* JEOCIE: */ /** Interrupt enable for injected channels. */
#define ADC_CR1_JEOCIE			(1 << 7)

/* AWDIE: */ /** Analog watchdog interrupt enable. */
#define ADC_CR1_AWDIE			(1 << 6)

/* EOCIE: */ /** Interrupt enable EOC. */
#define ADC_CR1_EOCIE			(1 << 5)

/* AWDCH[4:0]: Analog watchdog channel bits. (Up to 17 other values reserved) */
/* Notes:
 * ADC1: Analog channel 16 and 17 are internally connected to the temperature
 * sensor and V_REFINT, respectively.
 * ADC2: Analog channel 16 and 17 are internally connected to V_SS.
 * ADC3: Analog channel 9, 14, 15, 16 and 17 are internally connected to V_SS.
 */
/****************************************************************************/
/* ADC_CR1 AWDCH[4:0] ADC watchdog channel */
/** @defgroup adc_watchdog_channel ADC watchdog channel
@ingroup STM32F1xx_adc_defines

@{*/
#define ADC_CR1_AWDCH_CHANNEL0		(0x00 << 0)
#define ADC_CR1_AWDCH_CHANNEL1		(0x01 << 0)
#define ADC_CR1_AWDCH_CHANNEL2		(0x02 << 0)
#define ADC_CR1_AWDCH_CHANNEL3		(0x03 << 0)
#define ADC_CR1_AWDCH_CHANNEL4		(0x04 << 0)
#define ADC_CR1_AWDCH_CHANNEL5		(0x05 << 0)
#define ADC_CR1_AWDCH_CHANNEL6		(0x06 << 0)
#define ADC_CR1_AWDCH_CHANNEL7		(0x07 << 0)
#define ADC_CR1_AWDCH_CHANNEL8		(0x08 << 0)
#define ADC_CR1_AWDCH_CHANNEL9		(0x09 << 0)
#define ADC_CR1_AWDCH_CHANNEL10		(0x0A << 0)
#define ADC_CR1_AWDCH_CHANNEL11		(0x0B << 0)
#define ADC_CR1_AWDCH_CHANNEL12		(0x0C << 0)
#define ADC_CR1_AWDCH_CHANNEL13		(0x0D << 0)
#define ADC_CR1_AWDCH_CHANNEL14		(0x0E << 0)
#define ADC_CR1_AWDCH_CHANNEL15		(0x0F << 0)
#define ADC_CR1_AWDCH_CHANNEL16		(0x10 << 0)
#define ADC_CR1_AWDCH_CHANNEL17		(0x11 << 0)
/**@}*/
#define ADC_CR1_AWDCH_MASK		(0x1F << 0)
#define ADC_CR1_AWDCH_SHIFT		0


/* ALIGN: Data alignement. */
#define ADC_CR2_ALIGN_RIGHT             (0 << 11)
#define ADC_CR2_ALIGN_LEFT              (1 << 11)
#define ADC_CR2_ALIGN			(1 << 11)

/* DMA: Direct memory access mode. (ADC1 and ADC3 only!) */
#define ADC_CR2_DMA			(1 << 8)

/* CONT: Continous conversion. */
#define ADC_CR2_CONT			(1 << 1)

/* ADON: A/D converter On/Off. */
/* Note: If any other bit in this register apart from ADON is changed at the
 * same time, then conversion is not triggered. This is to prevent triggering
 * an erroneous conversion.
 * Conclusion: Must be separately written.
 */
#define ADC_CR2_ADON			(1 << 0)


/* --- ADC_JOFRx, ADC_HTR, ADC_LTR values ---------------------------------- */

#define ADC_JOFFSET_LSB			0
#define ADC_JOFFSET_MSK			(0x7ff << 0)
#define ADC_HT_LSB			0
#define ADC_HT_MSK			(0x7ff << 0)
#define ADC_LT_LSB			0
#define ADC_LT_MSK			(0x7ff << 0)

#define ADC_SQR1_L_LSB			20

/* --- ADC_JSQR values ----------------------------------------------------- */

#define ADC_JSQR_JL_LSB			20
#define ADC_JSQR_JSQ4_LSB		15
#define ADC_JSQR_JSQ3_LSB		10
#define ADC_JSQR_JSQ2_LSB		5
#define ADC_JSQR_JSQ1_LSB		0

/* JL[2:0]: Discontinous mode channel count injected channels. */
/****************************************************************************/
/** @defgroup adc_jsqr_jl ADC Number of channels in discontinuous mode fro injected channels.
@ingroup STM32F1xx_adc_defines

@{*/
#define ADC_JSQR_JL_1CHANNELS       (0x0 << ADC_JSQR_JL_LSB)
#define ADC_JSQR_JL_2CHANNELS       (0x1 << ADC_JSQR_JL_LSB)
#define ADC_JSQR_JL_3CHANNELS       (0x2 << ADC_JSQR_JL_LSB)
#define ADC_JSQR_JL_4CHANNELS       (0x3 << ADC_JSQR_JL_LSB)
/**@}*/
#define ADC_JSQR_JL_SHIFT		13
#define ADC_JSQR_JL_MSK			(0x2 << ADC_JSQR_JL_LSB)
#define ADC_JSQR_JSQ4_MSK		(0x1f << ADC_JSQR_JSQ4_LSB)
#define ADC_JSQR_JSQ3_MSK		(0x1f << ADC_JSQR_JSQ3_LSB)
#define ADC_JSQR_JSQ2_MSK		(0x1f << ADC_JSQR_JSQ2_LSB)
#define ADC_JSQR_JSQ1_MSK		(0x1f << ADC_JSQR_JSQ1_LSB)

/* --- ADC_JDRx, ADC_DR values --------------------------------------------- */

#define ADC_JDATA_LSB			0
#define ADC_DATA_LSB			0
#define ADC_ADC2DATA_LSB		16 /* ADC1 only (dual mode) */
#define ADC_JDATA_MSK			(0xffff << ADC_JDATA_LSB)
#define ADC_DATA_MSK			(0xffff << ADC_DA)
#define ADC_ADC2DATA_MSK		(0xffff << ADC_ADC2DATA_LSB)
					/* ADC1 only (dual mode) */

/* --- Function prototypes ------------------------------------------------- */

BEGIN_DECLS

void adc_power_on(u32 adc);
void adc_start_conversion_direct(u32 adc);
void adc_set_single_channel(u32 adc, u8 channel);
void adc_set_dual_mode(u32 mode);
bool adc_eoc(u32 adc);
bool adc_eoc_injected(u32 adc);
u32 adc_read_regular(u32 adc);
u32 adc_read_injected(u32 adc, u8 reg);
void adc_set_injected_offset(u32 adc, u8 reg, u32 offset);
void adc_enable_analog_watchdog_regular(u32 adc);
void adc_disable_analog_watchdog_regular(u32 adc);
void adc_enable_analog_watchdog_injected(u32 adc);
void adc_disable_analog_watchdog_injected(u32 adc);
void adc_enable_discontinuous_mode_regular(u32 adc, u8 length);
void adc_disable_discontinuous_mode_regular(u32 adc);
void adc_enable_discontinuous_mode_injected(u32 adc);
void adc_disable_discontinuous_mode_injected(u32 adc);
void adc_enable_automatic_injected_group_conversion(u32 adc);
void adc_disable_automatic_injected_group_conversion(u32 adc);
void adc_enable_analog_watchdog_on_all_channels(u32 adc);
void adc_enable_analog_watchdog_on_selected_channel(u32 adc, u8 channel);
void adc_enable_scan_mode(u32 adc);
void adc_disable_scan_mode(u32 adc);
void adc_enable_eoc_interrupt_injected(u32 adc);
void adc_disable_eoc_interrupt_injected(u32 adc);
void adc_enable_awd_interrupt(u32 adc);
void adc_disable_awd_interrupt(u32 adc);
void adc_enable_eoc_interrupt(u32 adc);
void adc_disable_eoc_interrupt(u32 adc);
void adc_enable_temperature_sensor(u32 adc);
void adc_disable_temperature_sensor(u32 adc);
void adc_start_conversion_regular(u32 adc);
void adc_start_conversion_injected(u32 adc);
void adc_disable_external_trigger_regular(u32 adc);
void adc_disable_external_trigger_injected(u32 adc);
void adc_set_left_aligned(u32 adc);
void adc_set_right_aligned(u32 adc);
void adc_enable_dma(u32 adc);
void adc_disable_dma(u32 adc);
void adc_reset_calibration(u32 adc);
void adc_calibration(u32 adc);
void adc_set_continuous_conversion_mode(u32 adc);
void adc_set_single_conversion_mode(u32 adc);
#ifdef __GNUC__
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR_ > 4)
void adc_on(u32 adc) __attribute__ ((deprecated ("will be removed in the first release")));
#else
void adc_on(u32 adc) __attribute__ ((deprecated));
#endif
#else
void adc_on(u32 adc);
#endif
void adc_off(u32 adc);
void adc_set_sample_time(u32 adc, u8 channel, u8 time);
void adc_set_sample_time_on_all_channels(u32 adc, u8 time);
void adc_set_watchdog_high_threshold(u32 adc, u16 threshold);
void adc_set_watchdog_low_threshold(u32 adc, u16 threshold);
void adc_set_regular_sequence(u32 adc, u8 length, u8 channel[]);
void adc_set_injected_sequence(u32 adc, u8 length, u8 channel[]);

END_DECLS

#endif
/**@}*/

