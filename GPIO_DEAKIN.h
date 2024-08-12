#ifndef GPIO_DEAKIN_H
#define GPIO_DEAKIN_H

class GPIO_DEAKIN {
public:
    bool Config_GPIO(char Port_Num, char Pin_Num, char pin_Mode);
    bool Write_GPIO(char Port_Num, char Pin_Num, bool State);
    bool Read_GPIO(char Port_Num, char Pin_Num);
    
    // New methods for controlling a group of GPIO pins
    bool Config_GPIO_Group(char Port_Num, char* PinArray, char pin_Mode, uint8_t numPins);
    bool GPIO_Display_Pattern(char Port_Num, char* PinArray, char GPIOPattern, uint8_t numPins);
    void GPIO_Running_Lights(char Port_Num, char* PinArray, uint8_t numPins, float delay_0_1ms);
};

#endif
