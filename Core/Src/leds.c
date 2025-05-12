/*
 * Led modes module
 */

#include "leds.h"

#include <stddef.h>

static void _reg_mode(leds_t* state, leds_mode_func func, leds_mode_func_isr func_isr);
static void _mode_1(leds_t* state);
static void _mode_2(leds_t* state);
static void _mode_3(leds_t* state);

// TODO:
//   static leds_mode_func _mode_4;
//   static leds_mode_func_isr _mode_4_isr;

void leds_init(leds_t* state, leds_pin_port_t leds[LEDS_NUMS]) {
    state->current_mode = 0;
    state->modes_count = 0;

    state->red = leds[0];
    state->green = leds[1];
    state->blue = leds[2];

    _reg_mode(state, _mode_1, NULL);
    _reg_mode(state, _mode_2, NULL);
    _reg_mode(state, _mode_3, NULL);
    // TODO: Add modes
}

void leds_off(leds_t* state) {
    LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
    LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
    LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);
    return;
}

void leds_next_mode(leds_t* state) {
    leds_off(state);
    state->current_mode++;
    if (state->current_mode > LEDS_MODES_NUMS) { state->current_mode %= LEDS_MODES_NUMS + 1; }

    if (LEDS_MODES_NUMS == state->current_mode) {
        leds_off(state);
    } else {
        state->modes[state->current_mode].func(state);
    }
}

uint8_t leds_get_current_mode(leds_t* state) { return state->current_mode; }

static void _reg_mode(leds_t* state, leds_mode_func func, leds_mode_func_isr func_isr) {
    leds_mode_handler_t new_mode = {func, func_isr};
    state->modes[state->modes_count++] = new_mode;
}

static void _mode_1(leds_t* state) {
    LL_GPIO_SetOutputPin(state->red.port, state->red.pin);
    return;
}

static void _mode_2(leds_t* state) {
    LL_GPIO_SetOutputPin(state->green.port, state->green.pin);
    return;
}

static void _mode_3(leds_t* state) {
    LL_GPIO_SetOutputPin(state->blue.port, state->blue.pin);
    return;
}