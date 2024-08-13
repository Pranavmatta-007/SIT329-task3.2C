#include "GPIO_DEAKIN.h"

GPIO_DEAKIN gpioController;
uint8_t pins[] = {1, 2, 3, 4, 5, 6};

void setup() {
  gpioController.configurePins(pins, 6, OUTPUT); // OUTPUT is assumed to be a valid mode
}

void loop() {
  gpioController.displayPattern(pins, 0b00000101, 6); // Display pattern
  delay(1000); // Wait for 1 second
  gpioController.sequentialOnOff(pins, 6, 500); // Run lights sequentially
}
