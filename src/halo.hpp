#pragma once

#include <stdint.h>

namespace Halo {

enum class PortId {
    PortA = 0,
    PortB,
    PortC,
    PortD,
    PortE,
    PortF,
    PortG,
    PortH
};

template<PortId port>
struct Port {
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
// Port<0> PortA;
// Port<1> PortB;
// Port<2> PortC;

enum class Pin {
    Pin0 = 0,
    Pin1 = 1,
    Pin2 = 2,
    Pin3 = 3,
    Pin4 = 4,
    Pin5 = 5,
    Pin7 = 7,
    Pin12 = 12,
    Pin13 = 13,
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

template<PortId portEnum, Pin pinEnum>
struct DigitalPin : DigitalPinBase {
    static constexpr uint32_t portIndex = static_cast<uint32_t>(portEnum);
    static constexpr uint32_t pinIndex = static_cast<uint32_t>(pinEnum);

    constexpr static uint32_t peripheralBase = 0x40020000u; // AHB1 base address
    constexpr static uint32_t portBase = peripheralBase + (0x0400u * portIndex);
    constexpr static uint32_t pinMask = (1u << pinIndex);

    void operator=(bool value) {
        constexpr static uint32_t address = portBase + 0x14u; // ODR register address
        if (value) {
            *((volatile uint32_t *)address) |= (1 << pinIndex);
        } else {
            *((volatile uint32_t *)address) &= ~(1 << pinIndex);
        }
    }
    static struct {
        operator bool() {
            constexpr static uint32_t address = portBase + 0x10u; // IDR register address
            return ((*((volatile uint32_t *)address)) & pinMask) ? true : false;
        }
    } pressed;

    static struct {
        void operator=(Mode mode) {
            constexpr static uint32_t address = portBase + 0x00u; // MODER register address
            uint32_t moder = *((volatile uint32_t *)address);
            moder &= ~(0x3u << (pinIndex * 2)); // Clear the mode bits for the pin
            moder |= (static_cast<uint32_t>(mode) << (pinIndex * 2)); // Set the new mode
            *((volatile uint32_t *)address) = moder;
        }
    } mode;
    static struct {
        void operator=(bool onoff) {
            constexpr static uint32_t address = portBase + 0x04u; // OTYPER register address
            if (onoff) {
                *((volatile uint32_t *)address) |= pinMask;
            } else {
                *((volatile uint32_t *)address) &= ~pinMask;
            }
        }
    } openDrain;

};

};  // namespaceh Halo
