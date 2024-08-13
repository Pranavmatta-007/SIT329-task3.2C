#ifndef GPIO_DEAKIN_H
#define GPIO_DEAKIN_H

class GPIO_DEAKIN {
public:
  bool Config_GPIO(char PortNum, char PinNum, char Mode);
  bool Write_GPIO(char PortNum, char PinNum, bool State);
  bool Read_GPIO(char PortNum, char PinNum);
  bool configurePins(uint8_t pinArray[], uint8_t size, uint8_t mode);
  bool displayPattern(uint8_t pinArray[], uint8_t pattern, uint8_t size);
  void sequentialOnOff(uint8_t pinArray[], uint8_t size, int delayTime);
};
#endif
