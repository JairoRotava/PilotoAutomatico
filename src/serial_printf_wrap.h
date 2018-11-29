#ifndef SERIAL_PRINTF_WRAP_h
#define SERIAL_PRINTF_WRAP_h

#include <Arduino.h>

void p(const char *fmt, ... );
void p(const __FlashStringHelper *fmt, ... );

#endif