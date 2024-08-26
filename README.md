# Pico-Learning-Project

Pico Development Notes


Things I want to learn:
- DMA Transfers
- PIO

Problems I’m solving:
- Output seems really coarse.. I dunno why

Misc Notes to Self:
- The USB Serial port will disappear when the program ends. 
- Consider using the serial UART for printf’s
- When using the SWD debugger UART stays connected. For sure the way to go. 

Dev Env Setup

Setup a home folder:
- mkdir pico-dev

ARM Toolchains:
- cd pico-dev
- wget https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
- tar -xvzf toolchain.file
- export PICO_TOOLCHAIN_PATH=/path/to/your/toolchain

Pico SDK:
- git clone https://github.com/raspberrypi/pico-sdk.git 
- cd pico-sdk 
- git submodule update --init 
- export PICO_SDK_PATH=$(pwd)

Picotool:
* git clone https://github.com/raspberrypi/picotool.git
* cd picotool 
* mkdir build 
* cd build 
* cmake .. 
* make
* cp picotool /usr/local/bin


export PICO_TOOLCHAIN_PATH=~/Downloads/pico-dev/arm-toolchain


Build:
- From the build sub folder in my-project: 
    - cmake .. -DPICO_SDK_PATH=~/Downloads/pico-dev/pico-sdk  -DPICO_BOARD=adafruit_feather_rp2040
    - 
    - make

SWD / Debug / OpenOCD

OpenOCD:
- https://github.com/xpack-dev-tools/openocd-xpack/releases

PICO Firmware:
https://github.com/raspberrypi/debugprobe
https://github.com/raspberrypi/debugprobe/releases
https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf (See Page 20)

Serial Monitor:
- Screen /dev/tty.usbmodem1102 115200
- For the serial monitor to work you need the following in CMakeLists.txt
    - pico_enable_stdio_usb(i2c-scanner 0)
    - pico_enable_stdio_uart(i2c-scanner 1)

Flashing command: 
* ./bin/openocd -f openocd/scripts/interface/cmsis-dap.cfg -f openocd/scripts/target/rp2040.cfg -c "adapter speed 5000" -c "program digital-synth.elf verify reset exit"
* ./bin/openocd -f openocd/scripts/interface/cmsis-dap.cfg -f openocd/scripts/target/rp2040.cfg -c "init" -c "reset halt" -c "flash erase_sector 0 0 0x10" -c "shutdown"
    * Ran this because I was getting flash verify failures
* Reset the microcontroller:
    * ./bin/openocd -f openocd/scripts/interface/cmsis-dap.cfg -f openocd/scripts/target/rp2040.cfg -c "adapter speed 5000" -c "init; reset; exit"
    * 
￼




