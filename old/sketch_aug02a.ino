#include "usb_dev.h"

const int pinLED = 13;

void setup() {
  pinMode(pinLED, OUTPUT);

  usb_init();

  while (usb_configuration == 0) {
    delay(5000);
    digitalWrite(pinLED, HIGH);
    delay(5000);
    digitalWrite(pinLED, LOW);
  }

  digitalWrite(pinLED, LOW);
}

void loop() {
  uint8_t buffer[64] = { 0 };

  usb_rawhid_recv(&buffer, 300000);

  for (int i = 0; i < 64; i++) {
    if (buffer[i] > 0) {
      // Short flashes signal "receieved"
      digitalWrite(pinLED, HIGH);
      delay(100);
      digitalWrite(pinLED, LOW);
      delay(100);
      digitalWrite(pinLED, HIGH);
      delay(100);
      digitalWrite(pinLED, LOW);
      delay(100);
      digitalWrite(pinLED, HIGH);
      delay(100);
      digitalWrite(pinLED, LOW);
      break;
    }
  }

  // Long flash is "waiting"
  digitalWrite(pinLED, HIGH);
  delay(1000);
  digitalWrite(pinLED, LOW);
}
