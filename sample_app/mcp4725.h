#ifndef MCP4725_H
#define MCP4725_H

#include <stdint.h>
#include "hardware/i2c.h"

// Define the I2C address of the MCP4725
#define MCP4725_ADDR 0x60

// Function prototypes
bool MCP4725_init(i2c_inst_t *i2c, uint8_t addr);
void MCP4725_set_voltage(uint16_t output, bool writeEEPROM);

#endif // MCP4725_H

