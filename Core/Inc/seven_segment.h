#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include <stdint.h>

typedef enum seg_dot { SEG_DOT, SEG_NOT_DOT } seg_dot_t;

void seg_set_digit(uint8_t digit);
void seg_set_dot(seg_dot_t dot_state);

#endif  // SEVEN_SEGMENT_H
