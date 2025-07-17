# Toolchain file for arm-none-eabi-g++

# Set the system name for cross-compilation
SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR arm)

# Specify the compilers
SET(CMAKE_C_COMPILER arm-none-eabi-gcc)
SET(CMAKE_CXX_COMPILER arm-none-eabi-g++)
SET(CMAKE_ASM_COMPILER arm-none-eabi-as)

set(CMAKE_CROSS_COMPILING TRUE)
set(CMAKE_TRY_COMPILE FALSE)

set(CMAKE_LINKER arm-none-eabi-gcc)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T/Users/frankw/Projects/Sandbox/halo/stm32f429.ld")

# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -T/Users/frankw/Projects/Sandbox/halo/stm32f429.ld")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib")

# Specify the root of the toolchain (adjust if necessary)
# For example, if your toolchain is in /usr/local/arm-none-eabi
# SET(CMAKE_FIND_ROOT_PATH /usr/local/arm-none-eabi)

# Set the sysroot for the toolchain
# SET(CMAKE_SYSROOT ${CMAKE_FIND_ROOT_PATH}/arm-none-eabi/libc)

# Enable cross-compilation
# SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
