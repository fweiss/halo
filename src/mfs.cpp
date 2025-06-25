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
}

// on F429 with default clocks, bit-banged pulse is 312 ns
// the FM74HC595 shift register allows for up to 24 MHz
void MultiFunctionShield ::tick() {
    led1 = button.pressed;

    serialDataInput = serialData & 0x01;
    shiftClock = true;
    shiftClock = false;
    serialData >>= 1;
    state++;
    if (state > 0x0F) {
        state = 0;
        serialData = 0x80EE; // Reset serial data to a known value
        latchClock = true;
        latchClock = false;
    }
}