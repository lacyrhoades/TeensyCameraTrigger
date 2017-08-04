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

    ledOff();

    // Start all pins high
    resetPins();
}

void loop() {
    byte buffer[64] = { 0 };

    // wait for input, give up after 1 minute
    usb_rawhid_recv(&buffer, 60000);

    ledOn();

    // if 1 min of no activity
    // ... or if we intentionally got a "reset" packet
    // reset the pins to this output (aka all pins HIGH)
    if (buffer[0] == 0x00) {
      resetPins();
    }

    // We got focus byte
    if (buffer[0] == 0x0F) {
      byte input = buffer[1];
      byte output = 0x00;

      // spread out 0b11111111 to 0b01010101
      output |= (input << 0) & 0b00000001;
      output |= (input << 1) & 0b00000100;
      output |= (input << 2) & 0b00010000;
      output |= (input << 3) & 0b01000000;

      GPIOD_PDOR = GPIOD_PDOR & (output ^ 0xFF);
    }

    // Fire byte or un-fire byte
    if (buffer[0] == 0xFF || buffer[0] == 0xFE) {
      byte input = buffer[1];
      byte output = 0x00;

      // spread out 0b11111111 to 0b10101010
      output |= (input << (1 + 0)) & 0b00000010;
      output |= (input << (1 + 1)) & 0b00001000;
      output |= (input << (1 + 2)) & 0b00100000;
      output |= (input << (1 + 3)) & 0b10000000;

      if (buffer[0] == 0xFE) {
        // UN-FIRE SHUTTER
        GPIOD_PDOR = GPIOD_PDOR ^ output;
      } else {
        // FIRE SHUTTER
        GPIOD_PDOR = GPIOD_PDOR & (output ^ 0xFF);
      }
    }

    delay(100);

    ledOff();
}

void setOutput(byte output) {
  // PULL FOCUS
  // 00000000 register
  // 01010101 ouput
  // 10101010 inverse
  // 00000000 register & inverse

  // 10101010 register
  // 01010101 output
  // 10101010 inverse
  // 10101010 register & inverse

  // 01010101 register
  // 01010101 output
  // 10101010 inverse
  // 00000000 register & inverse

  // 11111111 register
  // 10101010 output
  // 01010101 inverse
  // 00000000 register & inverse

  // 00000000 register
  // 00000000 output
  // 11111111 inverse
  // 00000000 register & inverse
  GPIOD_PDOR = GPIOD_PDOR & (output ^ 0xFF);
}

void resetPins() {
    // RESET PINS
    GPIOD_PDOR = GPIOD_PDIR | 0b11111111;
}

void ledOn() {
    // LED ON
    GPIOC_PDOR = GPIOC_PDIR | 0b00100000;
}

void ledOff() {
    // LED OFF
    GPIOC_PDOR = GPIOC_PDIR & 0b11011111;
}

