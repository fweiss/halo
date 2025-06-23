// #include "stm32f4xx.h"
#include "halo.hpp"

int main(void) {
    using namespace Halo;

    Port<PortId::PortB>::clockEnable = true;

    DigitalPin<PortId::PortB, Pin::Pin7> blueLed;
    blueLed.mode = DigitalPinBase::Mode::Output;

    DigitalPin<PortId::PortB, Pin::Pin0> greenLed;
    greenLed.mode = DigitalPinBase::Mode::Output;
    greenLed = true;

    DigitalPin<PortId::PortB, Pin::Pin14> redLed;
    redLed.mode = DigitalPinBase::Mode::Output;
    redLed = true;

    Port<PortId::PortC>::clockEnable = true;
    DigitalPin<PortId::PortC, Pin::Pin13> blueButton;
    // blueButton::Mode::Input); // PC13 is input

    for (;;) {
        if (blueButton.pressed) {
            blueLed = true;
        } else {
            blueLed = false;
        }
    }

    return 0 ;
}
