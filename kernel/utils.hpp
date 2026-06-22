#pragma once

#include <stdint.h>

inline const char* int_to_string(int n) {
  static char buf[12];
  char* p = buf + 11;
  bool neg = n < 0;

  *p = '\0';

  do {
    *--p = '0' + (neg ? -(n % 10) : n % 10);
    n /= 10;
  } while (n);

  if (neg)
    *--p = '-';

  return p;
}

inline void outb(uint16_t port, uint8_t val) {
  asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
  return ret;
}