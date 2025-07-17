# Developer setup on MAC
By default, cmake will use the macOS CLang toolchain
instead of ``arm-none-eabi-g++``.
This is resolved by using a toolchain file.

> Maybe we're using the wrong cmake?

## Compiling and flashing
When setup, the following commands should be used in the build directory:
- ``export export CMAKE_TOOLCHAIN_FILE=../arm-none-eabi-cxx.cmake``
- ``cmake ..``
- ``openocd -f ../f429-flash.cfg``

> You can skip the export on subsequent builds.

## installl arm-none-eabi-gcc
- apple silicon
- x86-64 (14.2.rel1)

``brew install arm-none-eabi-gcc``
> This download and builds everything. Maybe prune it?

``/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-g++``

had to update from monterey 12.2 to Sequoia 15.5


/Users/frankw/.platformio/packages/toolchain-gccarmnoneeabi/bin/arm-none-eabi-g++
4.8.4

/Applications/ArmGNUToolchain/13.2.Rel1
13.2.rel1

set PATH=/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin:$PATH

``cmake -DCMAKE_TOOLCHAIN_FILE=../arm-none-eabi-cxx.cmake ..``

## install open-ocd 0.12.0
``brew install open-ocd``

``openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg -c "program f429-bare.elf verify reset" -c shutdown``



