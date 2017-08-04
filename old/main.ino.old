#include <Arduino.h>
#include "usb_dev.h"

const int pinLED = 13; // register C, bit 5

void setup() {
    pinMode(pinLED, OUTPUT);

    // All pins in D register
    pinMode(2, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(20, OUTPUT);
    pinMode(21, OUTPUT);
    pinMode(5, OUTPUT);

    usb_init();

    // Start high
    GPIOD_PDOR = GPIOD_PDIR | 0b11111111;
}

void loop() {
    uint8_t buffer[64] = { 0 };

    usb_rawhid_recv(&buffer, 300000);

    if (buffer[0] == 0xFF) {
        // LED ON
        GPIOC_PDOR = GPIOC_PDIR | 0b00100000;

        byte input = buffer[1];

        // PULL FOCUS
        // input packet: 0b11111111

        // output = (val << 1) & (mask >> 6)
        // output = 0b11111110 & 0b11
        // output = 0b00000010

        // val = val & (mask << 2)
        // val = 0b11111111 & (0b11111100)

        // output &= (val << 1) & (mask >> 4)
        // output = 0b11111000 & 0b1111
        // output = 0b00001010

        // repeat...

        byte mask = 0xFF;
        byte output = 0x00;

        for (int i = 1; i <= 4; i++) {
            output = (input << i) & (mask >> (8 - i*2));
            input = input & (mask << i * 2);
        }

        // i.e. GPIOD_PDOR = buffer[1] & 0b10101010;
        GPIOD_PDOR = output;

        // FIRE SHUTTER
        // GPIOD_PDOR = GPIOD_PDIR & 0b01010101;

        delay(100);

        // LED OFF
        GPIOC_PDOR = GPIOC_PDIR & 0b11011111;
    }
}
