#include "GPIO_DEAKIN.h"

bool GPIO_DEAKIN::Config_GPIO(char PortNum, char PinNum, char Mode) {
  PortGroup *port;
  if (PortNum == 'A') {
    port = &PORT->Group[0];
  } else if (PortNum == 'B') {
    port = &PORT->Group[1];
  } else {
    return false;
  }

  if (Mode == OUTPUT) {
    port->DIRSET.reg = (1 << PinNum);
  } else if (Mode == INPUT) {
    port->DIRCLR.reg = (1 << PinNum);
  } else {
    return false;
  }

  return true;
}

bool GPIO_DEAKIN::Write_GPIO(char PortNum, char PinNum, bool State) {
  PortGroup *port;
  if (PortNum == 'A') {
    port = &PORT->Group[0];
  } else if (PortNum == 'B') {
    port = &PORT->Group[1];
  } else {
    return false;
  }

  if (State == HIGH) {
    port->OUTSET.reg = (1 << PinNum);
  } else if (State == LOW) {
    port->OUTCLR.reg = (1 << PinNum);
  } else {
    return false;
  }

  return true;
}

bool GPIO_DEAKIN::Read_GPIO(char PortNum, char PinNum) {
  PortGroup *port;
  if (PortNum == 'A') {
    port = &PORT->Group[0];
  } else if (PortNum == 'B') {
    port = &PORT->Group[1];
  } else {
    return false;
  }

  return (port->IN.reg & (1 << PinNum)) != 0;
}
#include "GPIO_DEAKIN.h"
#include "Arduino.h"

// Assuming these functions are defined elsewhere in your project
extern bool Config_GPIO(char PortNum, char PinNum, char Mode);
extern bool Write_GPIO(char PortNum, char PinNum, bool State);
extern bool Read_GPIO(char PortNum, char PinNum);

bool GPIO_DEAKIN::configurePins(uint8_t pinArray[], uint8_t size, uint8_t mode) {
  bool result = true;
  for (int i = 0; i < size; i++) {
    result &= Config_GPIO(0, pinArray[i], mode);  // Assuming PortNum is always 0 for simplicity
  }
  return result;
}

bool GPIO_DEAKIN::displayPattern(uint8_t pinArray[], uint8_t pattern, uint8_t size) {
  bool result = true;
  for (int i = 0; i < size; i++) {
    bool state = pattern & (1 << i);
    result &= Write_GPIO(0, pinArray[i], state);  // Assuming PortNum is always 0
  }
  return result;
}

void GPIO_DEAKIN::sequentialOnOff(uint8_t pinArray[], uint8_t size, int delayTime) {
  for (int i = 0; i < size; i++) {
    Write_GPIO(0, pinArray[i], true);  // Turn on
    delay(delayTime);
    Write_GPIO(0, pinArray[i], false);  // Turn off
  }
  for (int i = size - 1; i >= 0; i--) {
    Write_GPIO(0, pinArray[i], true);  // Turn on
    delay(delayTime);
    Write_GPIO(0, pinArray[i], false);  // Turn off
  }
}
