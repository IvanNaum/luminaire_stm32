/*
 * Led modes module
 */

#include "leds.h"

#include <stddef.h>

static void _reg_mode(leds_t* state, leds_mode_func func, leds_mode_func_isr func_isr);
static void _mode_red(leds_t* state);
static void _mode_green(leds_t* state);
static void _mode_blue(leds_t* state);
static void _mode_color_cycle(leds_t* state);
static void _mode_color_cycle_isr(leds_t* state);
static void _mode_red_alert(leds_t* state);
static void _mode_red_alert_isr(leds_t* state);
static void _mode_running_light(leds_t* state);
static void _mode_running_light_isr(leds_t* state);
static void _mode_all_blink(leds_t* state);
static void _mode_all_blink_isr(leds_t* state);
static void _mode_counter_motion(leds_t* state);
static void _mode_counter_motion_isr(leds_t* state);
static void _mode_police_strobe(leds_t* state);
static void _mode_police_strobe_isr(leds_t* state);

void leds_init(leds_t* state, leds_pin_port_t leds[LEDS_NUMS]) {
    state->modes_count = 0;

    state->red = leds[0];
    state->green = leds[1];
    state->blue = leds[2];

    (void)_mode_red;
    (void)_mode_green;
    (void)_mode_blue;

    _reg_mode(state, _mode_red, NULL);
    _reg_mode(state, _mode_green, NULL);
    _reg_mode(state, _mode_blue, NULL);
    _reg_mode(state, _mode_color_cycle, _mode_color_cycle_isr);
    _reg_mode(state, _mode_red_alert, _mode_red_alert_isr);
    _reg_mode(state, _mode_running_light, _mode_running_light_isr);
    _reg_mode(state, _mode_all_blink, _mode_all_blink_isr);
    _reg_mode(state, _mode_counter_motion, _mode_counter_motion_isr);
    _reg_mode(state, _mode_police_strobe, _mode_police_strobe_isr);
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

static void _mode_red(leds_t* state) {
    LL_GPIO_SetOutputPin(state->red.port, state->red.pin);
    return;
}

static void _mode_green(leds_t* state) {
    LL_GPIO_SetOutputPin(state->green.port, state->green.pin);
    return;
}

static void _mode_blue(leds_t* state) {
    LL_GPIO_SetOutputPin(state->blue.port, state->blue.pin);
    return;
}

static void _mode_color_cycle(leds_t* state) { (void)state; }
static void _mode_color_cycle_isr(leds_t* state) {
    static uint32_t count = 0;

    if (count >= 300) count = 0;  // Полный цикл: 300 тиков = 3 сек (6 фаз * 0.5 сек)

    // Каждая комбинация длится 0.5 сек (50 тиков = 500 мс)
    switch (count / 50) {  // 50 тиков на фазу
        case 0:            // Красный
            LL_GPIO_SetOutputPin(state->red.port, state->red.pin);
            LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
            LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);
            break;
        case 1:  // Красный + Зеленый (желтый)
            LL_GPIO_SetOutputPin(state->red.port, state->red.pin);
            LL_GPIO_SetOutputPin(state->green.port, state->green.pin);
            LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);
            break;
        case 2:  // Зеленый
            LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
            LL_GPIO_SetOutputPin(state->green.port, state->green.pin);
            LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);
            break;
        case 3:  // Зеленый + Синий (голубой)
            LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
            LL_GPIO_SetOutputPin(state->green.port, state->green.pin);
            LL_GPIO_SetOutputPin(state->blue.port, state->blue.pin);
            break;
        case 4:  // Синий
            LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
            LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
            LL_GPIO_SetOutputPin(state->blue.port, state->blue.pin);
            break;
        case 5:  // Синий + Красный (пурпурный)
            LL_GPIO_SetOutputPin(state->red.port, state->red.pin);
            LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
            LL_GPIO_SetOutputPin(state->blue.port, state->blue.pin);
            break;
    }

    count++;
}

static void _mode_red_alert(leds_t* state) { (void)state; }
static void _mode_red_alert_isr(leds_t* state) {
    static uint32_t count = 0;

    if (count >= 40) count = 0;  // Полный цикл: 40 тиков = 0.4 сек

    // Красный мигает 0.2 сек вкл/0.2 сек выкл
    if (count == 0) {
        LL_GPIO_SetOutputPin(state->red.port, state->red.pin);
    } else if (count == 20) {  // 20 тиков = 200 мс
        LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
    }

    // Гасим другие светодиоды
    LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
    LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);

    count++;
}

static void _mode_running_light(leds_t* state) { (void)state; }
static void _mode_running_light_isr(leds_t* state) {
    static uint32_t count = 0;

    if (count >= 90) count = 0;  // Полный цикл: 90 тиков = 0.9 сек (3 светодиода * 0.3 сек)

    // Каждый светодиод горит 0.3 сек (30 тиков = 300 мс)
    switch (count / 30) {  // 30 тиков на светодиод
        case 0:            // Красный
            LL_GPIO_SetOutputPin(state->red.port, state->red.pin);
            LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
            LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);
            break;
        case 1:  // Зеленый
            LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
            LL_GPIO_SetOutputPin(state->green.port, state->green.pin);
            LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);
            break;
        case 2:  // Синий
            LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
            LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
            LL_GPIO_SetOutputPin(state->blue.port, state->blue.pin);
            break;
    }

    count++;
}

static void _mode_all_blink(leds_t* state) { (void)state; }
static void _mode_all_blink_isr(leds_t* state) {
    static uint32_t count = 0;

    if (count >= 100) count = 0;  // Полный цикл: 100 тиков = 1 сек (10 мс * 100)

    // Все светодиоды мигают синхронно (0.5 сек вкл/0.5 сек выкл)
    if (count == 0) {
        LL_GPIO_SetOutputPin(state->red.port, state->red.pin);
        LL_GPIO_SetOutputPin(state->green.port, state->green.pin);
        LL_GPIO_SetOutputPin(state->blue.port, state->blue.pin);
    } else if (count == 50) {  // 50 тиков = 500 мс
        LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
        LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
        LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);
    }

    count++;
}

static void _mode_counter_motion(leds_t* state) { (void)state; }

static void _mode_counter_motion_isr(leds_t* state) {
    static uint32_t count = 0;
    const uint32_t CYCLE = 120;  // Полный цикл: 120 тиков = 1.2 сек

    if (count >= CYCLE) count = 0;

    // Фазы:
    if (count < 20) {
        // Красный движется к центру (0.2 сек)
        LL_GPIO_SetOutputPin(state->red.port, state->red.pin);
        LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
        LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);
    } else if (count < 40) {
        // Синий движется к центру (0.2 сек)
        LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
        LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
        LL_GPIO_SetOutputPin(state->blue.port, state->blue.pin);
    } else if (count < 60) {
        // Зеленый вспыхивает в центре (0.2 сек)
        LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
        LL_GPIO_SetOutputPin(state->green.port, state->green.pin);
        LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);
    } else if (count < 80) {
        // Синий возвращается (0.2 сек)
        LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
        LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
        LL_GPIO_SetOutputPin(state->blue.port, state->blue.pin);
    } else if (count < 100) {
        // Красный возвращается (0.2 сек)
        LL_GPIO_SetOutputPin(state->red.port, state->red.pin);
        LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
        LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);
    } else {
        // Пауза перед новым циклом (0.2 сек)
        LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
        LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
        LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);
    }

    count++;
}
static void _mode_police_strobe(leds_t* state) { (void)state; }

static void _mode_police_strobe_isr(leds_t* state) {
    static uint32_t count = 0;
    static uint8_t phase = 0;  // 0: красный, 1: синий

    // Счетчик для миганий (0-9: 5 миганий на цвет, так как вкл+выкл = 2 тика)
    if (count >= 10) {
        count = 0;
        phase = !phase;  // Смена фазы
    }

    // Управление светодиодами
    if (phase == 0) {
        // Фаза красного: мигание каждые 0.1 сек (10 тиков)
        if (count % 2 == 0) {
            LL_GPIO_SetOutputPin(state->red.port, state->red.pin);
            LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);
        } else {
            LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
        }
    } else {
        // Фаза синего: мигание каждые 0.1 сек
        if (count % 2 == 0) {
            LL_GPIO_SetOutputPin(state->blue.port, state->blue.pin);
            LL_GPIO_ResetOutputPin(state->red.port, state->red.pin);
        } else {
            LL_GPIO_ResetOutputPin(state->blue.port, state->blue.pin);
        }
    }

    // Гасим зеленый всегда
    LL_GPIO_ResetOutputPin(state->green.port, state->green.pin);
    count++;
}
