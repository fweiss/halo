cmake_minimum_required(VERSION 3.28.2)

project(f429-bare CXX ASM)

add_executable(${PROJECT_NAME}.elf src/main.cpp src/startup.s)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

set(CMAKE_CROSS_COMPILING TRUE)
set(CMAKE_TRY_COMPILE FALSE)

set(CMAKE_LINKER arm-none-eabi-gcc)
# questionable: --specs=nosys.specs-flto -freestanding
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -T../stm32f429.ld")

# set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb")
# questionable: -fno-builtin  -ffreestanding
set(COMMON_FLAGS "${CPU_FLAGS} -Wall -Wextra -Os")

set(CMAKE_C_FLAGS "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS}")


add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMAND arm-none-eabi-objcopy -O ihex   ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
)
