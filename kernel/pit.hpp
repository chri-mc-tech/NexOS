#pragma once
#include "utils.hpp"

inline uint16_t pit_get_count() {
  outb(0x43, 0x00);
  uint8_t low = inb(0x40);
  uint8_t high = inb(0x40);
  return ((uint16_t)high << 8) | low;
}

inline void sleep_ms(uint32_t ms) {
  outb(0x43, 0x34);
  outb(0x40, 0xFF);
  outb(0x40, 0xFF);

  uint32_t target_ticks = ms * 1193;
  uint32_t elapsed_ticks = 0;

  uint16_t last_tick = pit_get_count();

  while (elapsed_ticks < target_ticks) {
    uint16_t current_tick = pit_get_count();
    uint16_t delta = last_tick - current_tick;

    elapsed_ticks += delta;
    last_tick = current_tick;
  }
}