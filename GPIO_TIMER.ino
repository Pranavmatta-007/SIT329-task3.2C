#include "GPIO_TIMER.h"

// Assuming TIMER_DEAKIN manages only one specific timer for simplicity, e.g., TC4
#define TIMER_REG TC4

bool GPIO_TIMER::config_timer(uint8_t timerNum, uint16_t startCount, uint16_t endCount, uint8_t resolution) {
    // Configure generic clock for the timer and set prescaler
    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(TC4_GCLK_ID) | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_CLKEN;
    while (GCLK->STATUS.bit.SYNCBUSY);

    TIMER_REG->COUNT16.CTRLA.reg = TC_CTRLA_MODE_COUNT16;  // Set timer to 16-bit mode
    while (TIMER_REG->COUNT16.STATUS.bit.SYNCBUSY);

    TIMER_REG->COUNT16.CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1024 | TC_CTRLA_ENABLE;  // Set prescaler and enable
    while (TIMER_REG->COUNT16.STATUS.bit.SYNCBUSY);

    TIMER_REG->COUNT16.CC[0].reg = (uint16_t)(endCount * resolution);
    while (TIMER_REG->COUNT16.STATUS.bit.SYNCBUSY);

    return true;
}

uint32_t GPIO_TIMER::getTC_count(uint8_t timerNum) {
    return TIMER_REG->COUNT16.COUNT.reg;
}

void GPIO_TIMER::wait(uint16_t period) {
    uint32_t startTime = getTC_count(4);
    while ((getTC_count(4) - startTime) < period);
}

void GPIO_TIMER::enable_timer(uint8_t timerNum) {
    TIMER_REG->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
    while (TIMER_REG->COUNT16.STATUS.bit.SYNCBUSY);
}

void GPIO_TIMER::disable_timer(uint8_t timerNum) {
    TIMER_REG->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
    while (TIMER_REG->COUNT16.STATUS.bit.SYNCBUSY);
}
