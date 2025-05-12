#include "seven_segment.h"

#include <stm32g030xx.h>

#include "main.h"
#include "stm32g0xx_ll_gpio.h"

#define _SEG_NUMS (7)

static uint8_t _seg_digit[] = {
    0b0111111,  // 0  (abcdef)
    0b0000110,  // 1  (bc)
    0b1011011,  // 2  (abdeg)
    0b1001111,  // 3  (abcdg)
    0b1100110,  // 4  (bcfg)
    0b1101101,  // 5  (acdfg)
    0b1111101,  // 6  (abcdefg)
    0b0000111,  // 7  (abc)
    0b1111111,  // 8  (abcdefg)
    0b1101111,  // 9  (abcdfg)
};
static uint32_t _seg_digit_pins[] = {
    SEG_A_Pin, SEG_B_Pin, SEG_C_Pin, SEG_D_Pin, SEG_E_Pin, SEG_F_Pin, SEG_G_Pin,
};
static GPIO_TypeDef* _seg_digit_ports[] = {SEG_A_GPIO_Port, SEG_B_GPIO_Port, SEG_C_GPIO_Port, SEG_D_GPIO_Port,
                                           SEG_E_GPIO_Port, SEG_F_GPIO_Port, SEG_G_GPIO_Port};

void seg_set_digit(uint8_t digit) {
    if (digit > sizeof(_seg_digit) / sizeof(_seg_digit[0])) { return; }

    for (int i = 0; i < _SEG_NUMS; ++i) {
        if (_seg_digit[digit] >> i & 1) {
            LL_GPIO_SetOutputPin(_seg_digit_ports[i], _seg_digit_pins[i]);
        } else {
            LL_GPIO_ResetOutputPin(_seg_digit_ports[i], _seg_digit_pins[i]);
        }
    }
}

void seg_dot_enable() { LL_GPIO_SetOutputPin(SEG_P_GPIO_Port, SEG_P_Pin); }
void seg_dot_disable() { LL_GPIO_ResetOutputPin(SEG_P_GPIO_Port, SEG_P_Pin); }
void seg_dot_toggle() { LL_GPIO_TogglePin(SEG_P_GPIO_Port, SEG_P_Pin); }
