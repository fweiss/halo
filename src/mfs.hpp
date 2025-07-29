#pragma once

#include "halo.hpp"

using namespace Halo;

// maybe call it OneShot?
struct Latch {
    void operator=(bool value) {
        latchedState = value;
    }
    operator bool() {
        bool returnValue = latchedState;
        latchedState = false;
        return returnValue;
    }
    bool latchedState;
};

// Button class to handle button press logic
template<DigitalPin<PortId::PortC, Pin::Pin3> &buttonPin>
class Button {
public:
    Button() : lastState(false) {}
    void tick() {
        const bool currentState = ! buttonPin.pressed;
        const bool edgeDetected = (currentState != lastState);
        if (edgeDetected) {
            pressed = currentState;
            released = ! currentState;
        }
        lastState = currentState;
    }
    Latch pressed;
    Latch released;

// private:
    bool lastState;
};

class MultiFunctionShield {
public:
    MultiFunctionShield();
    void tick();
    void outputDigit(uint8_t digitIndex);

    DigitalPin<PortId::PortA, Pin::Pin5> led1;
    DigitalPin<PortId::PortC, Pin::Pin0> button;
    static DigitalPin<PortId::PortC, Pin::Pin3> button2;
    Button<button2> incrementButton;

    DigitalPin<PortId::PortF, Pin::Pin12> serialDataInput;
    DigitalPin<PortId::PortF, Pin::Pin13> shiftClock;
    DigitalPin<PortId::PortF, Pin::Pin14> latchClock;

    uint8_t state;

    uint16_t serialData;
    uint8_t serialDataIndex;

    struct Display {
        uint8_t getSegments(uint8_t digitIndex) const;
        uint8_t segments[4];
        void operator=(uint16_t value);
    } display;
    void displayShift(uint16_t parallelData);

};