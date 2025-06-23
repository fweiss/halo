// #include "stm32f4xx.h"
#include "helpers.hpp"
#include "halo.hpp"

int main(void) {
    Peripheral::PortBlockB.clockEnable = true;

    DigitalPin<Port::PortB, Pin::Pin7> blueLed;
    blueLed.mode = DigitalPinBase::Mode::Output;

    DigitalPin<Port::PortB, Pin::Pin0> greenLed;
    greenLed.mode = DigitalPinBase::Mode::Output;
    greenLed = true;

    DigitalPin<Port::PortB, Pin::Pin14> redLed;
    redLed.mode = DigitalPinBase::Mode::Output;
    redLed = true;

    PortC::clockEnable = true;
    Button<PortC, Pin13> blueButton;
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
