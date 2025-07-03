#include "mfs.hpp"

MultiFunctionShield::MultiFunctionShield() {
    using namespace Halo;
    Port<PortId::PortF>::clockEnable = true;
    Port<PortId::PortA>::clockEnable = true;
    
    led1.mode = DigitalPinBase::Mode::Output;
    led1.openDrain = true;

    Port<PortId::PortC>::clockEnable = true;

    serialDataInput.mode = DigitalPinBase::Mode::Output;
    shiftClock.mode = DigitalPinBase::Mode::Output;
    latchClock.mode = DigitalPinBase::Mode::Output;

    serialDataIndex = 0;
    serialData = 0x1012;
    state = 0;

    display = 1234;
}

// on F429 with default clocks, bit-banged pulse is 312 ns
// the FM74HC595 shift register allows for up to 24 MHz
void MultiFunctionShield ::tick() {
    led1 = button.pressed;
    incrementButton.tick();

    outputDigit(0);
    outputDigit(1);
    outputDigit(2);
    outputDigit(3);
}

void MultiFunctionShield::outputDigit(uint8_t digitIndex) {
    // Ensure digitIndex is within bounds
    // upper 4 bits select digit
    // lower 8 bits select segments, but reversed polarity
    uint16_t parallelData = 0x8000u >> digitIndex;
    // parallelData |= (~digits.segments[digitIndex]) & 0xFFu;
    parallelData |= (~display.segments[digitIndex]) & 0xFFu;
    for (uint8_t i = 0; i < 16; i++) {
        serialDataInput = parallelData & 0x01;
        shiftClock = true;
        shiftClock = false;
        parallelData >>= 1;
    }
    latchClock = true;
    latchClock = false;
}

void MultiFunctionShield::Display::operator=(uint16_t value) {
    segments[0] = getSegments((value / 1000) % 10); // thousands
    segments[1] = getSegments((value / 100) % 10);  // hundreds
    segments[2] = getSegments((value / 10) % 10);   // tens
    segments[3] = getSegments(value % 10);          // units
}

uint8_t MultiFunctionShield::Display::getSegments(uint8_t digitIndex) const {
    // segments are labeled clockwise a-g, 
    // with a = 0x80, b = 0x40, c = 0x20, d = 0x10, e = 0x08, f = 0x04, g = 0x02, dp = 0x01
    static const uint8_t segments[10] = {
        0b11111100, // 0
        0b01100000, // 1
        0b11011010, // 2
        0b11110010, // 3
        0b01100110, // 4
        0b10110110, // 5
        0b10111110, // 6
        0b11100000, // 7
        0b11111110, // 8
        0b11110110  // 9
    };
    if (digitIndex < 10) {
        return segments[digitIndex];
    }
    return 0; // Return 0 for invalid digit index
}
