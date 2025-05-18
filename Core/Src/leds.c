/*
 * Led modes module
 */

#include "leds.h"

#include <stddef.h>

static void _reg_mode(leds_t* state, leds_mode_func func, leds_mode_func_isr func_isr);
static void _mode_1(leds_t* state);
static void _mode_2(leds_t* state);
static void _mode_3(leds_t* state);
static void _mode_4(leds_t* state);
static void _mode_4_isr(leds_t* state);

void leds_init(leds_t* state, leds_pin_port_t leds[LEDS_NUMS]) {
    state->modes_count = 0;

    state->red = leds[0];
    state->green = leds[1];
    state->blue = leds[2];

    _reg_mode(state, _mode_1, NULL);
    _reg_mode(state, _mode_2, NULL);
    _reg_mode(state, _mode_3, NULL);
    _reg_mode(state, _mode_4, _mode_4_isr);
    // TODO: Add modes

    state->current_mode = state->modes_count;
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
    if (state->current_mode > state->modes_count) { state->current_mode %= state->modes_count + 1; }

    if (state->current_mode == state->modes_count) {
        leds_off(state);
    } else {
        state->modes[state->current_mode].func(state);
    }
}

uint8_t leds_get_current_mode(leds_t* state) {
    if (state->current_mode == state->modes_count) {
        return 0;
    } else {
        return state->current_mode + 1;
    }
}

leds_mode_func_isr leds_get_func_isr(leds_t* state) {
    if (state->current_mode == state->modes_count) {
        return NULL;
    } else {
        return state->modes[state->current_mode].func_isr;
    }
}

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

static void _mode_4(leds_t* state) {
    if (state == NULL) { return; }
}
static void _mode_4_isr(leds_t* state) {
    static uint32_t count = 0;

    if (count == 0) { LL_GPIO_SetOutputPin(state->blue.port, state->blue.pin); }

    if (count == 1000) { LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin); }

    if (count == 2000) { count = 0; }

    count++;
}
