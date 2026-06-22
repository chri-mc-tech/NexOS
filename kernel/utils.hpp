#pragma once
#include <stdint.h>

inline const char* int_to_string(int number) {
  static char buffer[12];
  char* current_char = &buffer[11];
  *current_char = '\0';

  unsigned int value = (number < 0) ? -number : number;

  do {
    *--current_char = '0' + (value % 10);
    value /= 10;
  } while (value > 0);

  if (number < 0) {
    *--current_char = '-';
  }

  return current_char;
}


inline void outb(uint16_t port, uint8_t val) {
  asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
  return ret;
}