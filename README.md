``wsl -d cortex``
``sudo apt install gcc-arm-none-eabi``
``arm-none-eabi-gcc (15:13.2.rel1-2) 13.2.1 20231009``
``sudo apt install stlink-tools``

```
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -nostdlib -Tstm32f429.ld -o blinky.elf src/startup.s src/main.c
arm-none-eabi-objcopy -O binary blinky.elf blinky.bin
st-flash write blinky.bin 0x8000000
```

> ``undefined reference to `NMI_Handler'``

> ``WARN usb.c: Couldn't find any ST-Link devices``

## st-link on windows
- download from stlink.org
- unzip

> libusb-1.0.dll not found
> put it in bin along with st-flash

> unknown chipis 0x419

Chip id is ``0x0419``. See ``st-info --chipid``

## ``C:/Program Files (x86)/stlink/config/chips: No such file or directory``
> Copy stlink/config directory.

## Falsh loader run error
``st-flash write ../../blinky.bin 0x8000000``

- leds flash
- erase: OK
- write error code ?

. hard reset of nucleo fixed it!

## Flash and run, but no blinky.
- red led, indicates initialization between PC and stlink is complete

> Code used LED_PIN 5

GPIOA5

## New flash
- download stlink
- unzip
- copy and rename to stlink
- copy config to program files

On Windows: ``cd stlink/bin``, then ``st-flash write ../../blinky.bin 0x8000000``

## Links and references
https://www.st.com/resource/en/user_manual/um1974-stm32-nucleo144-boards-mb1137-stmicroelectronics.pdf


