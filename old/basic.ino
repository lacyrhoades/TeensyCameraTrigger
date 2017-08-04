#include <Arduino.h>
#include "usb_dev.h"

const int pinLED = 13; // register C, bit 5

void setup() {
    pinMode(pinLED, OUTPUT);
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
    delay(5000);

    // LED ON
    GPIOC_PDOR = GPIOC_PDIR | 0b00100000;

    // FOCUS
    GPIOD_PDOR = GPIOD_PDIR & 0b10101010;

    delay(1300);

    // LED OFF
    GPIOC_PDOR = GPIOC_PDIR & 0b11011111;

    // FIRE
    // GPIOD_PDOR = GPIOD_PDIR & 0b01010101;

    delay(80);

    // RESET
    GPIOD_PDOR = GPIOD_PDIR | 0b11111111;

    delay(300000);
}
