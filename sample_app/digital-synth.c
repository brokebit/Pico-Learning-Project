#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "mcp4725.h"

#define OUTPUT_FREQ 10000 
#define SAMPLE_FREQ 160000
#define TWO_32 4294967296.0

volatile unsigned int phase_accum_main;
volatile unsigned int phase_incr_main = (OUTPUT_FREQ*TWO_32)/SAMPLE_FREQ;

// DDS sine table
#define sine_table_size 256
volatile int sine_table[sine_table_size];

bool repeating_timer_callback(__unused struct repeating_timer *t) {
	phase_accum_main += phase_incr_main;
	uint16_t value = (sine_table[phase_accum_main>>24] + 2048) & 0xffff;
	MCP4725_set_voltage(value, false);
	//printf("%i\n", (sine_table[phase_accum_main>>24] + 2048) & 0xffff);
	return true;
}

int main() {
	stdio_init_all();
	printf("Getting ready to init\n");
	sleep_ms(2000);
	printf("Accum: %i\n", phase_incr_main);
	// Initialize I2C at 400kHz
	i2c_init(i2c0, 100 * 30000);
	gpio_set_function(12, GPIO_FUNC_I2C);
	gpio_set_function(13, GPIO_FUNC_I2C);
	gpio_pull_up(12);
	gpio_pull_up(13);
	bi_decl(bi_2pins_with_func(12, 13, GPIO_FUNC_I2C));

	bool init_result; 
	// Initialize the MCP4725
	init_result = MCP4725_init(i2c0, MCP4725_ADDR);
	if (!init_result) {
		printf("Error initalizing MCP4725\n");
	} else {
		printf("MCP4725 initalized successfuly\n");
	}

	init_result = MCP4725_init(i2c0, MCP4725_ADDR);

	printf("Done initializing!\n");
	printf("Sending write commind in 10 seconds\n");	
	sleep_ms(10000);
	uint16_t x = 2457;
       
	MCP4725_set_voltage(x, false);

	
	// Build the sine table
	//
	int ii = 0;
	for (ii = 0; ii<sine_table_size; ii++) {
		sine_table[ii] = (int)(2047*sin((float)ii*6.283/(float)sine_table_size));
	}

	struct repeating_timer timer;
	add_repeating_timer_us(1/SAMPLE_FREQ, repeating_timer_callback, NULL, &timer);

	while (true) {
		// printf("Hello, World!\n");
		sleep_ms(1000);
	}
}

