#include "GPIO_DEAKIN.h"
#include "TIMER_DEAKIN.h"

GPIO_DEAKIN gpio;

void setup() {
    char pins[6] = {1, 2, 3, 4, 5, 6};
    
    // Configure the 6 pins as outputs
    gpio.Config_GPIO_Group('A', pins, 'O', 6);
}

void loop() {
    char pins[6] = {1, 2, 3, 4, 5, 6};
    char pattern = 0b00000101;  // Example pattern with LED 1 and 3 on

    // Display the pattern
    gpio.GPIO_Display_Pattern('A', pins, pattern, 6);

    // Wait for 1 second
    delay(1000);

    // Run the running lights pattern
    gpio.GPIO_Running_Lights('A', pins, 6, 10000.0);  // 1 second per LED
}
