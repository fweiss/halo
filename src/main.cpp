// #include "stm32f4xx.h"
#include "halo.hpp"
#include "mfs.hpp"

int main(void) {

    MultiFunctionShield mfs;

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

    uint16_t counter = 0;
    for (;;) {
        if (blueButton.pressed) {
            blueLed = true;
        } else {
            blueLed = false;
        }
        mfs.tick();
        if (mfs.incrementButton.released) {
            counter += 1;
        }
        mfs.display = counter;
    }

    return 0 ;
}
