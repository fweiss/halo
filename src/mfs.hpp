#pragma once

#include "halo.hpp"

using namespace Halo;

class MultiFunctionShield {
public:
    MultiFunctionShield();
    void tick();

    DigitalPin<PortId::PortA, Pin::Pin5> led1;
    DigitalPin<PortId::PortC, Pin::Pin0> button;

    DigitalPin<PortId::PortF, Pin::Pin12> serialDataInput;
    DigitalPin<PortId::PortF, Pin::Pin13> shiftClock;
    DigitalPin<PortId::PortF, Pin::Pin14> latchClock;

    uint8_t state;

    uint16_t serialData;
    uint8_t serialDataIndex;
};