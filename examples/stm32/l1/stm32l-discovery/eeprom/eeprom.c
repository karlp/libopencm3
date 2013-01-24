/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2013 Karl Palsson <karlp@tweak.net.au>
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

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#ifndef STM32L1  /* Helps completion in the ide... */
#define STM32L1
#endif
#include <libopencm3/cm3/common.h>
#include <libopencm3/stm32/l1/rcc.h>
#include <libopencm3/stm32/l1/flash.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dac.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>


#define USART_CONSOLE USART2
#define PORT_DISCOVERY_USER_LED		GPIOB
#define PIN_DISCOVERY_USER_LED		GPIO7
#define PORT_DISCOVERY_USER_BUTTON	GPIOA
#define PIN_DISCOVERY_USER_BUTTON	GPIO0

#define PIN_ANALOG_SOURCE		GPIO1
#define CHANNEL_ANALOG_SOURCE		1
#define PIN_ANALOG_TEST			GPIO4
#define CHANNEL_ANALOG_TEST		4
#define PIN_DAC				GPIO5
#define DAC_CHANNEL			CHANNEL_2

/*
 * Packed is optional, but aligned (4) is required!
 * (We only write out whole words to avoid dealing with the byte/hword write 
 * problem on medium density devices)
 */
struct example_eeprom_blob {
	int i;			// 4
	bool flag;		// 1
	int64_t ourdword;	// 8
	uint16_t halfword;	// 2
	bool flags_are_fun;	// 1
	bool flags_are_really_fun;	// 1
	float ourfloat;		// 4
} __attribute__((packed)) __attribute__ ((aligned (4)));

//#define EEMEM __attribute__((section(".eeprom")))

/*
 * We can read directly out of eeprom, but we can't write to it easily,
 * so we have a ram copy that we modify then write back to eeprom as a blob
 */
// Couldn't get eeprom sections to do anything worth a damn :(
struct example_eeprom_blob *blob_eeprom = 0x08080040;
struct example_eeprom_blob blob_ram;

void clock_setup(void)
{
	rcc_clock_setup_pll(&clock_config[CLOCK_VRANGE1_HSI_PLL_32MHZ]);
	/* Lots of things on all ports... */
	rcc_peripheral_enable_clock(&RCC_AHBENR, RCC_AHBENR_GPIOAEN);
	rcc_peripheral_enable_clock(&RCC_AHBENR, RCC_AHBENR_GPIOBEN);

	/* Enable clocks for USART2 and DAC*/
	rcc_peripheral_enable_clock(&RCC_APB1ENR, RCC_APB1ENR_USART2EN);
	rcc_peripheral_enable_clock(&RCC_APB1ENR, RCC_APB1ENR_DACEN);

	/* and the ADC */
	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_ADC1EN);
}

void usart_setup(void)
{
	/* Setup GPIO pins for USART2 transmit. */
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
	/* Setup USART2 TX pin as alternate function. */
	gpio_set_af(GPIOA, GPIO_AF7, GPIO2);

	usart_set_baudrate(USART_CONSOLE, 115200);
	usart_set_databits(USART_CONSOLE, 8);
	usart_set_stopbits(USART_CONSOLE, USART_STOPBITS_1);
	usart_set_mode(USART_CONSOLE, USART_MODE_TX);
	usart_set_parity(USART_CONSOLE, USART_PARITY_NONE);
	usart_set_flow_control(USART_CONSOLE, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(USART_CONSOLE);
}

/**
 * Use USART_CONSOLE as a console.
 * @param file
 * @param ptr
 * @param len
 * @return
 */
int _write(int file, char *ptr, int len)
{
	int i;

	if (file == STDOUT_FILENO || file == STDERR_FILENO) {
		for (i = 0; i < len; i++) {
			if (ptr[i] == '\n') {
				usart_send_blocking(USART_CONSOLE, '\r');
			}
			usart_send_blocking(USART_CONSOLE, ptr[i]);
		}
		return i;
	}
	errno = EIO;
	return -1;
}

void adc_setup(void)
{
	// Make sure pins are setup for analog in!
	gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, PIN_ANALOG_SOURCE);
	gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, PIN_ANALOG_TEST);

	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_ADC1EN);
	// This is not implemented for l1 yet...  rcc_set_adcpre()
	// Use this from F4 -  adc_set_clk_prescale()
	adc_off(ADC1);
	adc_disable_scan_mode(ADC1);
	adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_4CYC);

	adc_power_on(ADC1);
	while ((ADC_SR(ADC1) & ADC_SR_ADONS) == 0) {
		;
	}
}

static inline void dac_set_trigger_source_sw(int channel) {
	if (channel == CHANNEL_1) {
		dac_set_trigger_source(DAC_CR_TSEL1_SW);
	} else if (channel == CHANNEL_2) {
		dac_set_trigger_source(DAC_CR_TSEL2_SW);
	}
}

void dac_setup(void)
{
	gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, PIN_DAC);

	dac_disable(DAC_CHANNEL);
	dac_disable_waveform_generation(DAC_CHANNEL);
	dac_enable(DAC_CHANNEL);
	dac_set_trigger_source_sw(DAC_CHANNEL);
}

u16 read_adc_naiive(u8 channel)
{
	adc_set_single_channel(ADC1, channel);
	adc_start_conversion_regular(ADC1);
	while (!adc_eoc(ADC1));
	u16 reg16 = adc_read_regular(ADC1);
	return reg16;
}

void dumpblob(const char *tag, struct example_eeprom_blob *blob) {
	printf("%s: i:%d, flag:%d, flag2:%d, half:%hu, dword=%lld, float=%f\n",
		tag, blob->i, blob->flag, blob->flags_are_fun,
		blob->halfword, blob->ourdword, blob->ourfloat);
}

int main(void)
{
	volatile int loopticks = 0;
	volatile bool gdbhacking = false;
	clock_setup();
	usart_setup();
	printf("hello! sizeof eepromblob = %d, address=%#lx\n", 
		sizeof(struct example_eeprom_blob), (u32)blob_eeprom);
	memcpy(&blob_ram, blob_eeprom, sizeof(struct example_eeprom_blob));
	dumpblob("ram", &blob_ram);
	
	gpio_mode_setup(PORT_DISCOVERY_USER_LED, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_DISCOVERY_USER_LED);
	gpio_mode_setup(PORT_DISCOVERY_USER_BUTTON, GPIO_MODE_INPUT, GPIO_PUPD_NONE, PIN_DISCOVERY_USER_BUTTON);
	adc_setup();
	dac_setup();
	
	u32 eeprom_addr = 0x08080004;
	u32 eeprom_variable = MMIO32(eeprom_addr);
	
	while (1) {
		loopticks++;
		u16 source = read_adc_naiive(CHANNEL_ANALOG_SOURCE);
		u16 test = read_adc_naiive(CHANNEL_ANALOG_TEST);
		dac_load_data_buffer_single(eeprom_variable, RIGHT12, CHANNEL_2);
		dac_software_trigger(CHANNEL_2);

		if (loopticks % 100000 == 0) {
			printf("tick: %d: source= %hu, eeprom=%lu, test=%hu\n",
				loopticks / 100000, source, eeprom_variable, test);
		}
		
		if (gpio_get(PORT_DISCOVERY_USER_BUTTON, PIN_DISCOVERY_USER_BUTTON)) {
			printf("trying to save %u as new target\n", source);
			eeprom_program_word(eeprom_addr, source);
		}
		if (gdbhacking) {
			gdbhacking = false;
			eeprom_program_words((u32)blob_eeprom, (u32*)&blob_ram, sizeof(struct example_eeprom_blob) / 4);
		}
		
		if (loopticks % 100000 == 0) {  /* LED on/off */
			gpio_toggle(PORT_DISCOVERY_USER_LED, PIN_DISCOVERY_USER_LED);
		}
	}

	return 0;
}
