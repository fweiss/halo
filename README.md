## f429-bare
Explore bare metal Nucleo F429ZI

## Setup on WSL
``wsl -d cortex``
``sudo apt install gcc-arm-none-eabi``
``arm-none-eabi-gcc (15:13.2.rel1-2) 13.2.1 20231009``
``sudo apt install stlink-tools``

```
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -nostdlib -Tstm32f429.ld -o blinky.elf src/startup.s src/main.c
arm-none-eabi-objcopy -O binary blinky.elf blinky.bin
st-flash write blinky.bin 0x8000000
```

> stlink doesn's work on WSL: ``WARN usb.c: Couldn't find any ST-Link devices``.
> There are ways to e get it to work, but for now,
> just use stlink on Windows.

## stlink on Windows
- download stlink
- unzip
- copy and rename to stlink
- copy config to program files

> libusb-1.0.dll not found
> put it in bin along with st-flash

> unknown chipis 0x419

Chip id is ``0x0419``. See ``st-info --chipid``

>``C:/Program Files (x86)/stlink/config/chips: No such file or directory``
> Copy stlink/config directory.

On Windows, flash as follows:
```cd stlink/bin
st-flash write ../../blinky.bin 0x8000000
```

## Flash loader run error
``st-flash write ../../blinky.bin 0x8000000``

- leds flash
- erase: OK
- write error code ?

. hard reset of nucleo fixed it!

## Flash and run, but no blinky.
- red led, indicates initialization between PC and stlink is complete

> Code used LED_PIN 5

GPIOA5

> LD2 (blue) stays off when board is reset. Only upload makes it work.

## Links and references
https://www.st.com/resource/en/user_manual/um1974-stm32-nucleo144-boards-mb1137-stmicroelectronics.pdf

[Cortex M4 Programming Manual](https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf)

[Perpherals Programming Manual](https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)

[stlink github repo](https://github.com/stlink-org/stlink)

[connecting to USB devices from WSL](https://devblogs.microsoft.com/commandline/connecting-usb-devices-to-wsl/)

