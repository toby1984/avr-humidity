# avr-humidity

This repo contains software I wrote to display temperature/humidity readings from a SHT3x sensor on a SSD1306-compatible OLED display (both connected using I2C) using an ATMega328.

No third-party libraries were used in this code, I wrote all device driver code in AVR assembly after spending far too many hours with datasheets and a logic analyzer. This is a mixed C/assembly project 
that I mainly wrote to dog-feed jAVR, my own AVR macro assembler, and make sure the generated ELF binaries can be linked with avr-ld/avr-gcc.

Currently there's no schematic for the circuit as this is still somewhat work in progress (need to use a low-power step-up converter instead of the LDO,use 1 Mhz crystal instead of 8 Mhz or even internal oscillator,exchange power led for a low-power one etc)

![Ball of wires](https://github.com/toby1984/avr-humidity/raw/master/screenshot.png)


