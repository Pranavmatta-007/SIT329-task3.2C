#include "GPIO_DEAKIN.h"
#include "sam.h"

// Configure a group of GPIO pins as either inputs or outputs
bool GPIO_DEAKIN::Config_GPIO_Group(char Port_Num, char* PinArray, char pin_Mode, uint8_t numPins) {
    PortGroup *port;
    if (Port_Num == 'A') {
        port = &PORT->Group[0];
    } else if (Port_Num == 'B') {
        port = &PORT->Group[1];
    } else {
        return false;
    }

    for (uint8_t i = 0; i < numPins; i++) {
        if (pin_Mode == 'O') { // OUTPUT mode
            port->DIRSET.reg |= (1 << PinArray[i]);
        } else if (pin_Mode == 'I') { // INPUT mode
            port->DIRCLR.reg |= (1 << PinArray[i]);
        } else {
            return false;
        }
    }
    return true;
}

// Control a group of GPIO pins to display a specified pattern
bool GPIO_DEAKIN::GPIO_Display_Pattern(char Port_Num, char* PinArray, char GPIOPattern, uint8_t numPins) {
    PortGroup *port;
    if (Port_Num == 'A') {
        port = &PORT->Group[0];
    } else if (Port_Num == 'B') {
        port = &PORT->Group[1];
    } else {
        return false;
    }

    for (uint8_t i = 0; i < numPins; i++) {
        if (GPIOPattern & (1 << i)) { // Check if the bit is set in the pattern
            port->OUTSET.reg |= (1 << PinArray[i]);
        } else {
            port->OUTCLR.reg |= (1 << PinArray[i]);
        }
    }
    return true;
}

// Create a running lights effect with a group of GPIO pins
void GPIO_DEAKIN::GPIO_Running_Lights(char Port_Num, char* PinArray, uint8_t numPins, float delay_0_1ms) {
    TIMER_DEAKIN timer;  // Assuming you have the TIMER_DEAKIN class implemented

    PortGroup *port;
    if (Port_Num == 'A') {
        port = &PORT->Group[0];
    } else if (Port_Num == 'B') {
        port = &PORT->Group[1];
    } else {
        return;
    }

    while (true) {
        // Turn on pins sequentially from Pin 1 to Pin numPins
        for (uint8_t i = 0; i < numPins; i++) {
            port->OUT
