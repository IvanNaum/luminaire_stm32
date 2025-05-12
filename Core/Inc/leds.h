/*
 * Led modes module
 */

#ifndef LEDS_H
#define LEDS_H

#include "stm32g0xx_ll_gpio.h"

#define LEDS_NUMS (3)
#define LEDS_MODES_NUMS (9)

struct leds;

typedef void (*leds_mode_func)(struct leds* state);
typedef void (*leds_mode_func_isr)(struct leds* state);

typedef struct {
    GPIO_TypeDef* port;
    uint32_t pin;
} leds_pin_port_t;

typedef struct {
    leds_mode_func func;
    leds_mode_func_isr func_isr;
} leds_mode_handler_t;

typedef struct leds {
    leds_pin_port_t red;
    leds_pin_port_t green;
    leds_pin_port_t blue;
    uint8_t current_mode;
    uint8_t modes_count;
    leds_mode_handler_t modes[LEDS_MODES_NUMS];
} leds_t;

void leds_init(leds_t* state, leds_pin_port_t leds[LEDS_NUMS]);
void leds_off(leds_t* state);
void leds_next_mode(leds_t* state);
uint8_t leds_get_current_mode(leds_t* state);

#endif  // LEDS_H
