/** @addtogroup adc_file

@version 1.0.0

@author @htmlonly &copy; @endhtmlonly 2013 Karl Palsson <karlp@remake.is>

@date January 2013

This section of the library supports the L1 specific ADC functions.

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

/**@{*/

#include <libopencm3/stm32/l1/adc.h>

/*-----------------------------------------------------------------------------*/
/** @brief ADC Set the Sample Time for a Single Channel

The sampling time can be selected in ADC clock cycles from 4 to 384.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base.
@param[in] channel Unsigned int8. ADC Channel integer 0..18 or from @ref adc_channel.
@param[in] time Unsigned int8. Sampling time selection from @ref adc_sample_rg.
*/

void adc_set_sample_time(u32 adc, u8 channel, u8 time)
{
	u32 reg32;

	if (channel < 10) {
		reg32 = ADC_SMPR3(adc);
		reg32 &= ~(0x7 << (channel * 3));
		reg32 |= (time << (channel * 3));
		ADC_SMPR3(adc) = reg32;
	} else if (channel < 20) {
		reg32 = ADC_SMPR2(adc);
		reg32 &= ~(0x7 << ((channel - 10) * 3));
		reg32 |= (time << ((channel - 10) * 3));
		ADC_SMPR2(adc) = reg32;
	} else {
		reg32 = ADC_SMPR1(adc);
		reg32 &= ~(0x7 << ((channel - 20) * 3));
		reg32 |= (time << ((channel - 20) * 3));
		ADC_SMPR1(adc) = reg32;
	}
}

/*-----------------------------------------------------------------------------*/
/** @brief ADC Set the Sample Time for All Channels

The sampling time can be selected in ADC clock cycles, same for
all channels.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base.
@param[in] time Unsigned int8. Sampling time selection from @ref adc_sample_rg.
*/

void adc_set_sample_time_on_all_channels(u32 adc, u8 time)
{
	u8 i;
	u32 reg32 = 0;

	for (i = 0; i <= 9; i++)
		reg32 |= (time << (i * 3));
	ADC_SMPR0(adc) = reg32;
	ADC_SMPR1(adc) = reg32;
	ADC_SMPR2(adc) = reg32;
	ADC_SMPR3(adc) = reg32;
}

/*-----------------------------------------------------------------------------*/
/** @brief ADC Enable The Temperature Sensor

This enables both the sensor and the reference voltage measurements on channels
16 and 17.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base.
*/

void adc_enable_temperature_sensor(u32 adc)
{
	(void)adc; // Unused on L1
	ADC_CCR |= ADC_CCR_TSVREFE;
}

/*-----------------------------------------------------------------------------*/
/** @brief ADC Disable The Temperature Sensor

Disabling this will reduce power consumption from the sensor and the reference
voltage measurements.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base.
*/

void adc_disable_temperature_sensor(u32 adc)
{
	(void)adc; // Unused on L1
	ADC_CCR &= ~ADC_CCR_TSVREFE;
}


// TODO - these are copied from the F4 code! (F1 doesn't support polarity...)
/*-----------------------------------------------------------------------------*/
/** @brief ADC Enable an External Trigger for Regular Channels

This enables an external trigger for set of defined regular channels, and sets the
polarity of the trigger event: rising or falling edge or both. Note that if the
trigger polarity is zero, triggering is disabled.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base
@param[in] trigger Unsigned int32. Trigger identifier @ref adc_trigger_regular
@param[in] polarity Unsigned int32. Trigger polarity @ref adc_trigger_polarity_regular
*/

void adc_enable_external_trigger_regular(u32 adc, u32 trigger, u32 polarity)
{
	u32 reg32 = ADC_CR2(adc);

	reg32 &= ~(ADC_CR2_EXTSEL_MASK | ADC_CR2_EXTEN_MASK);
	reg32 |= (trigger | polarity);
	ADC_CR2(adc) = reg32;
}

/*-----------------------------------------------------------------------------*/
/** @brief ADC Disable an External Trigger for Regular Channels

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base
*/

void adc_disable_external_trigger_regular(u32 adc)
{
	ADC_CR2(adc) &= ~ADC_CR2_EXTEN_MASK;
}

