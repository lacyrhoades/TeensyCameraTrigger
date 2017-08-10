int currentProgram = 0;
unsigned long latestActivity = millis();

void setup() {
  // All pins in C register
  pinMode(15, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

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

  delay(100);
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
      GPIOC_PDOR = 0b00000000;
      GPIOD_PDOR = 0b00000000;
    } else {
      GPIOC_PDOR = GPIOC_PDOR & 0b10101010;
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
      GPIOC_PDOR = GPIOC_PDOR | 0xFF;
      GPIOD_PDOR = GPIOD_PDOR | 0xFF;
    } else {
      GPIOC_PDOR = GPIOC_PDOR | 0b10101010;
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
    GPIOC_PDOR = GPIOC_PDIR | 0b11111111;
}

