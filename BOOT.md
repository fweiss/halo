- boot[1:0] = 00: main flash 0x00000000 → 0x08000000
- boot[1:0] = 01: system memory 0x00000000 → 0x1FFF0000
- boot[1:0] = 10: embedded sram 0x00000000 → 0x20000000

> boot[0] tied low: boots from Flash at 0x08000000
