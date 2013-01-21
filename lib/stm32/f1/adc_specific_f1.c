/** @addtogroup adc_file

@version 1.0.0

@author @htmlonly &copy; @endhtmlonly 2013 Karl Palsson <karlp@remake.is>

@date January 2013

This section of the library supports the F1 specific ADC functions.

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

#include <libopencm3/stm32/f1/adc.h>

/*-----------------------------------------------------------------------------*/
/** @brief ADC Set the Sample Time for a Single Channel

The sampling time can be selected in ADC clock cycles from 1.5 to 239.5.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base.
@param[in] channel Unsigned int8. ADC Channel integer 0..18 or from @ref adc_channel.
@param[in] time Unsigned int8. Sampling time selection from @ref adc_sample_rg.
*/

void adc_set_sample_time(u32 adc, u8 channel, u8 time)
{
	u32 reg32;

	if (channel < 10) {
		reg32 = ADC_SMPR2(adc);
		reg32 &= ~(0x7 << (channel * 3));
		reg32 |= (time << (channel * 3));
		ADC_SMPR2(adc) = reg32;
	} else {
		reg32 = ADC_SMPR1(adc);
		reg32 &= ~(0x7 << ((channel - 10) * 3));
		reg32 |= (time << ((channel - 10) * 3));
		ADC_SMPR1(adc) = reg32;
	}
}

/*-----------------------------------------------------------------------------*/
/** @brief ADC Set the Sample Time for All Channels

The sampling time can be selected in ADC clock cycles from 1.5 to 239.5, same for
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
	ADC_SMPR2(adc) = reg32;

	for (i = 10; i <= 17; i++)
		reg32 |= (time << ((i - 10) * 3));
	ADC_SMPR1(adc) = reg32;
}

/*-----------------------------------------------------------------------------*/
/** @brief ADC Enable The Temperature Sensor

This enables both the sensor and the reference voltage measurements on channels
16 and 17.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base.
*/

void adc_enable_temperature_sensor(u32 adc)
{
	ADC_CR2(adc) |= ADC_CR2_TSVREFE;
}

/*-----------------------------------------------------------------------------*/
/** @brief ADC Disable The Temperature Sensor

Disabling this will reduce power consumption from the sensor and the reference
voltage measurements.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base.
*/

void adc_disable_temperature_sensor(u32 adc)
{
	ADC_CR2(adc) &= ~ADC_CR2_TSVREFE;
}

/*-----------------------------------------------------------------------------*/
/** @brief ADC Enable an External Trigger for Regular Channels

This enables an external trigger for set of defined regular channels.

For ADC1 and ADC2
@li Timer 1 CC1 event
@li Timer 1 CC2 event
@li Timer 1 CC3 event
@li Timer 2 CC2 event
@li Timer 3 TRGO event
@li Timer 4 CC4 event
@li EXTI (TIM8_TRGO is also possible on some devices, see datasheet)
@li Software Start

For ADC3
@li Timer 3 CC1 event
@li Timer 2 CC3 event
@li Timer 1 CC3 event
@li Timer 8 CC1 event
@li Timer 8 TRGO event
@li Timer 5 CC1 event
@li Timer 5 CC3 event
@li Software Start

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base.
@param[in] trigger Unsigned int8. Trigger identifier @ref adc_trigger_regular_12
for ADC1 and ADC2, or @ref adc_trigger_regular_3 for ADC3.
*/

void adc_enable_external_trigger_regular(u32 adc, u32 trigger)
{
	u32 reg32;

	reg32 = (ADC_CR2(adc) & ~(ADC_CR2_EXTSEL_MASK));
	reg32 |= (trigger);
	ADC_CR2(adc) = reg32;
	ADC_CR2(adc) |= ADC_CR2_EXTTRIG;
}

/*-----------------------------------------------------------------------------*/
/** @brief ADC Disable an External Trigger for Regular Channels

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base.
*/

void adc_disable_external_trigger_regular(u32 adc)
{
	ADC_CR2(adc) &= ~ADC_CR2_EXTTRIG;
}

/*-----------------------------------------------------------------------------*/
/** @brief ADC Enable an External Trigger for Injected Channels

This enables an external trigger for set of defined injected channels.

For ADC1 and ADC2
@li Timer 1 TRGO event
@li Timer 1 CC4 event
@li Timer 2 TRGO event
@li Timer 2 CC1 event
@li Timer 3 CC4 event
@li Timer 4 TRGO event
@li EXTI (TIM8 CC4 is also possible on some devices, see datasheet)
@li Software Start

For ADC3
@li Timer 1 TRGO event
@li Timer 1 CC4 event
@li Timer 4 CC3 event
@li Timer 8 CC2 event
@li Timer 8 CC4 event
@li Timer 5 TRGO event
@li Timer 5 CC4 event
@li Software Start

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base.
@param[in] trigger Unsigned int8. Trigger identifier @ref adc_trigger_injected_12
for ADC1 and ADC2, or @ref adc_trigger_injected_3 for ADC3.
*/
void adc_enable_external_trigger_injected(u32 adc, u32 trigger)
{
	u32 reg32;

	reg32 = (ADC_CR2(adc) & ~(ADC_CR2_JEXTSEL_MASK)); /* Clear bits [12:14]. */
	reg32 |= (trigger);
	ADC_CR2(adc) = reg32;
	ADC_CR2(adc) |= ADC_CR2_JEXTTRIG;
}

/*-----------------------------------------------------------------------------*/
/** @brief ADC Disable an External Trigger for Injected Channels

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base.
*/

void adc_disable_external_trigger_injected(u32 adc)
{
	ADC_CR2(adc) &= ~ADC_CR2_JEXTTRIG;
}

/*-----------------------------------------------------------------------------*/
/** @brief ADC Initialize Calibration Registers

This resets the calibration registers. It is not clear if this is required to be
done before every calibration operation.

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base.
*/

void adc_reset_calibration(u32 adc)
{
	ADC_CR2(adc) |= ADC_CR2_RSTCAL;
	while (ADC_CR2(adc) & ADC_CR2_RSTCAL);
}

/*-----------------------------------------------------------------------------*/
/** @brief ADC Calibration

The calibration data for the ADC is recomputed. The hardware clears the
calibration status flag when calibration is complete. This function does not return
until this happens and the ADC is ready for use.

The ADC must have been powered down for at least 2 ADC clock cycles, then powered on.
before calibration starts

@param[in] adc Unsigned int32. ADC block register address base @ref adc_reg_base.
*/
void adc_calibration(u32 adc)
{
	ADC_CR2(adc) |= ADC_CR2_CAL;
	while (ADC_CR2(adc) & ADC_CR2_CAL);
}
