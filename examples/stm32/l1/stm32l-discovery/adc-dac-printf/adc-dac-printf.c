/*
 * Karl Palsson, 2012 <karlp@tweak.net.au
 */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "syscfg.h"
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/l1/rcc.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dac.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>


static struct state_t state;

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
	gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO0);
	
	
	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_ADC1EN);
	// This is not implemented for l1 yet...  rcc_set_adcpre()
	// Use this from F4 -  adc_set_clk_prescale()
	adc_off(ADC1);
//	adc_disable_scan_mode(ADC1);
	ADC1_CR1 = 0;  // 12 bit,  no scan.
	//ADC_CR1(ADC1) = ADC_CR1_SCAN;
//	adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_4CYC);
	ADC1_CR2 = 0;  // no triggers, right aligned...
	//ADC_CR2(ADC1) = ADC_CR2_ALIGN_RIGHT | ADC_CR2_CONT;

//	ADC_SQR1(ADC1) = 0;
//	ADC_SQR5(ADC1) = 0;
	
	//adc_power_on(ADC1);
	ADC_CR2(ADC1) |= ADC_CR2_ADON;
	
	int i;
	for (i = 0; i < 100000; i++) /* Wait a bit. */
		__asm__("NOP");
	while ((ADC_SR(ADC1) & ADC_SR_ADONS) == 0) {
		;
	}

}

void dac_setup(void)
{
	gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO5);

	dac_disable(CHANNEL_2);
	dac_disable_waveform_generation(CHANNEL_2);
	dac_enable(CHANNEL_2);
	dac_set_trigger_source(DAC_CR_TSEL2_SW);
}

u16 read_adc_naiive(u8 channel)
{
	//u8 channel_array[16];
	//channel_array[0] = channel;
	//adc_set_regular_sequence(ADC1, 1, channel_array);
	adc_set_single_channel(ADC1, channel);
	adc_start_conversion_regular(ADC1);
	while (!adc_eoc(ADC1));
	u16 reg16 = adc_read_regular(ADC1);
	return reg16;
}

int main(void)
{
	int i;
	int j = 0;
	clock_setup();
	usart_setup();
	puts("hi guys!\n");
	gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO7);
	adc_setup();
	dac_setup();
	while (1) {
		u16 input_adc0 = read_adc_naiive(0);
		// TODO - write input_adc0/2 to dac....
		u16 target = input_adc0 / 2;
		dac_load_data_buffer_single(target, RIGHT12, CHANNEL_2);
		dac_software_trigger(CHANNEL_2);
		u16 input_adc1 = read_adc_naiive(1);
		printf("tick: %d: adc0= %u, target adc1=%d, adc1=%d\n",
			j++, input_adc0, target, input_adc1);
		gpio_toggle(GPIOB, GPIO7); /* LED on/off */
		for (i = 0; i < 100000; i++) /* Wait a bit. */
			__asm__("NOP");
	}

	return 0;
}
