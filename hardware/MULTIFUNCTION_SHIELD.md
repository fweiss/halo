# Muklti funbction shield

## TM74HC595
- Titan Microeletronics
- no max drive on dataasheet
- Vdd 2.0-5.5 V
- SDI - 8 - PF12
- SFTCLK - 7 - PF13
- LCHCLK - 4 - PF14

### issues
Even though the 3 signals generated for the '595 from the F429 are legit, the TM74HC595
fails to output correct logic signals to the LED segments.
The cause is 'F429 gives the shield 5 Vcc, but only gives 3.3 V signal levels.
Consequently, the '595 has a Vin of 3.6 V (72% of 5 V) but the logic
high output of the 'F429 is only 3.3 V.

Recommended to either:
- power '595 vcc at 3.3 V
- use 74HCT595 which works with 3.3 logic even when powered with 5 V

## LEDs
- D1 - 13 - PA5
- D2 - 12 - PA6
- D3 - 11 - PA7
- D4 - 10 - PD14

## buttons
- S1-A1 - PC0
- S2-A2 - PC3
- S3-A3 - PF3

## Potentiometer
- A0 - PA3

## display
- 3461BS
- continuous forward per dice (segment) 30 mA

## buzzer
- piezo
- PWM - D3 - PE13

## Links and references
[info on the shield](https://community.st.com/t5/stm32-mcus-products/im-trying-to-control-the-arduino-multifunction-shield-by-using/td-p/56923)

[multifunction shield schematic](https://static1.squarespace.com/static/584d41b3f5e2310b396cd953/t/5b2fbfb80e2e7265f3ecfa6d/1529855928655/Multifunction-Shield.pdf)


