#include <stdio.h>
#include "mcp4725.h"

static i2c_inst_t *i2c_instance;
static uint8_t i2c_addr;

void printb(uint8_t v) {
    unsigned int i, s = 1<<((sizeof(v)<<3)-1); // s = only most significant bit at 1
    for (i = s; i; i>>=1) printf("%d", v & i || 0 );
}



bool MCP4725_init(i2c_inst_t *i2c, uint8_t addr) {
	i2c_instance = i2c;
	i2c_addr = addr;
	uint8_t rxdata;

	int result = i2c_read_blocking(i2c_instance, i2c_addr, &rxdata, 1, false);

	printf("i2c result: %i", result);
	// Check if the device acknowledged
	if (result == PICO_ERROR_GENERIC) {
		// No acknowledgment received
		return false;
	} else {
		// Acknowledgment received
		return true;
	}
}

void MCP4725_set_voltage(uint16_t output, bool writeEEPROM) {
	uint8_t buffer[3];


	buffer[0] = 0x40;
	buffer[1] = output/16;
	buffer[2] = (output % 16) << 4;
	// printb(buffer[0]);
	// printf(" - ");
	// printb(buffer[1]);
	// printf(" - ");
	// printb(buffer[2]);
	// printf(" - %i\n",output);
	// Send the data over I2C
	i2c_write_blocking(i2c_instance, i2c_addr, buffer, 3, false);
}

