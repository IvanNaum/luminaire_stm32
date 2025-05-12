#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include <stdint.h>

typedef enum seg_dot { SEG_DOT, SEG_NOT_DOT } seg_dot_t;

void seg_set_digit(uint8_t digit);

void seg_dot_enable();
void seg_dot_disable();
void seg_dot_toggle();

#endif  // SEVEN_SEGMENT_H
