cmake_minimum_required(VERSION 3.13)

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(digital-synth)

pico_sdk_init()

add_executable(digital-synth digital-synth.c mcp4725.c)

target_link_libraries(digital-synth pico_stdlib hardware_i2c pico_binary_info)

pico_add_extra_outputs(digital-synth)
pico_enable_stdio_usb(digital-synth 0)
pico_enable_stdio_uart(digital-synth 1)
