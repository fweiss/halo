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

enum class Port {
    PortA = 0,
    PortB,
    PortC,
    PortD,
    PortE,
    PortF,
    PortG,
    PortH
};
enum class Pin {
    Pin0 = 0,
    Pin7 = 7,
    Pin14 = 14,
    Pin28 = 28,
};

struct DigitalPinBase {
    enum class Mode {
        Input,
        Output,
        AlternateFunction,
        Analog
    };
};

template<Port portEnum, Pin pinEnum>
struct DigitalPin : DigitalPinBase {
    static constexpr uint32_t portIndex = static_cast<uint32_t>(portEnum);
    static constexpr uint32_t pinIndex = static_cast<uint32_t>(pinEnum);

    constexpr static uint32_t peripheralBase = 0x40020000u; // AHB1 base address
    constexpr static uint32_t portBase = peripheralBase + (0x0400u * portIndex);

    void operator=(bool value) {
        constexpr static uint32_t address = portBase + 0x14u; // ODR register address
        if (value) {
            *((volatile uint32_t *)address) |= (1 << pinIndex);
        } else {
            *((volatile uint32_t *)address) &= ~(1 << pinIndex);
        }
    }
    static struct {
        void operator=(Mode mode) {
            constexpr static uint32_t address = portBase + 0x00u; // MODER register address
            uint32_t moder = *((volatile uint32_t *)address);
            moder &= ~(0x3u << (pinIndex * 2)); // Clear the mode bits for the pin
            moder |= (static_cast<uint32_t>(mode) << (pinIndex * 2)); // Set the new mode
            *((volatile uint32_t *)address) = moder;
        }
    } mode;
};

template<Port port>
struct PortBlock {
    constexpr static uint32_t RCC_BASE = 0x40023800u;
    constexpr static volatile uint32_t address = (RCC_BASE + 0x30u);
    constexpr static uint32_t enableMask = 0x1u << static_cast<uint32_t>(port);
    static struct {
        inline void operator=(bool onoff) {
            if (onoff) {
                *((uint32_t *)address) |= enableMask;
            } else {
                *((uint32_t *)address) &= ~enableMask;
            }
        }
    } clockEnable;
};

struct Peripheral {
    static PortBlock<Port::PortB> PortBlockB;
};
