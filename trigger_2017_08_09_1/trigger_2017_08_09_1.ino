const int pinLED = 13;
int currentProgram = 0;
unsigned long latestActivity = millis();

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

  resetPins();
  
  usbMIDI.setHandleNoteOn(onNoteOn);
  usbMIDI.setHandleNoteOff(onNoteOff);
  usbMIDI.setHandleProgramChange(onProgramChange);

  ledOn();
  delay(100);
  ledOff();
}

void loop() {
  if (usbMIDI.read()) {
    // Keep track of the last time we had a message
    latestActivity = millis();
  } else if (millis() - latestActivity > 30000) {
    // After 30 seconds, go high on all pins
    resetPins();
  }
}

void onNoteOn(byte channel, byte note, byte velocity) {
  if (currentProgram == 0) {
    if (velocity > 64) {
      GPIOD_PDOR = 0b00000000;
    } else {
      GPIOD_PDOR = GPIOD_PDOR & 0b10101010;
    }
  } else {
    if (velocity > 64) {
      GPIOD_PDOR = GPIOD_PDOR & ~(0b11 << note * 2);
    } else {
      GPIOD_PDOR = GPIOD_PDOR & ~(0b01 << note * 2);
    }
  }
}

void onProgramChange(byte channel, byte program) {
  if (currentProgram != program) {
    resetPins();
  }
  currentProgram = program;
}

void onNoteOff(byte channel, byte note, byte velocity) {
  if (currentProgram == 0) {
    if (velocity > 64) {
      GPIOD_PDOR = GPIOD_PDOR | 0xFF;
    } else {
      GPIOD_PDOR = GPIOD_PDOR | 0b10101010;
    }
  } else {
    if (velocity > 64) {
      GPIOD_PDOR = GPIOD_PDOR | 0b11 << note * 2;
    } else {
      GPIOD_PDOR = GPIOD_PDOR | 0b10 << note * 2;
    }
  }
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

