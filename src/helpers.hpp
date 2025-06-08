#pragma once

#include <stdint.h>

constexpr uint32_t Pin13 = 13u;

struct PortC {
    constexpr static uint32_t RCC_BASE = 0x40023800u;
    constexpr static volatile uint32_t address = (RCC_BASE + 0x30u);
    constexpr static uint32_t enableMask = 0x4u;
    static struct {
        void operator=(bool onoff) {
            if (onoff) {
                *((uint32_t *)address) |= enableMask;
            } else {
                *((uint32_t *)address) &= ~enableMask;
            }
        }
    } clockEnable;
};

template <typename Port, uint32_t Pin>
struct Button {
    constexpr static uint32_t peripheralBase = 0x40020000u; // AHB1 base address
    constexpr static uint32_t portCBase = peripheralBase + 0x0800u; // GPIOC base address
    constexpr static uint32_t address = (portCBase + 0x10u);
    static constexpr uint32_t pinMask = (1u << Pin);
    static struct {
        operator bool() {
            return ((*((volatile uint32_t *)address)) & pinMask) ? true : false;
        }
    } pressed;
};
