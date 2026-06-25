#pragma once
#include "pit.hpp"

enum VGA_color {
  BLACK = 0x0,
  BLUE = 0x1,
  GREEN = 0x2,
  CYAN = 0x3,
  RED = 0x4,
  MAGENTA = 0x5,
  BROWN = 0x6,
  LIGHT_GREY = 0x7,
  DARK_GREY = 0x8,
  LIGHT_BLUE = 0x9,
  LIGHT_GREEN = 0xA,
  LIGHT_CYAN = 0xB,
  LIGHT_RED = 0xC,
  LIGHT_MAGENTA = 0xD,
  YELLOW = 0xE,
  WHITE = 0xF
};

inline int cursor_offset = 320;

inline void set_cursor() {
  uint16_t pos = cursor_offset / 2;
  outb(0x3D4, 0x0E);
  outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
  outb(0x3D4, 0x0F);
  outb(0x3D5, (uint8_t)(pos & 0xFF));
}

inline void scroll() {
  char *vga = (char *) 0xB8000;
  while (cursor_offset >= 4000) {
    for (int i = 0; i < 3840; i++) {
      vga[i] = vga[i + 160];
    }
    for (int i = 3840; i < 4000; i += 2) {
      vga[i] = ' ';
      vga[i + 1] = WHITE;
    }
    cursor_offset -= 160;
  }
  set_cursor();
}

inline void print_char(char c, int color = LIGHT_GREY) {
  char *vga = (char *)0xB8000;

  if (c == '\n') {
    cursor_offset = (cursor_offset / 160 + 1) * 160;
    set_cursor();
    scroll();
    return;
  }
  if (c == '\b') {
    cursor_offset = cursor_offset - 2;
    vga[cursor_offset] = 0;
    set_cursor();
    scroll();
    return;
  }

  vga[cursor_offset] = c;
  vga[cursor_offset + 1] = color;

  cursor_offset += 2;

  scroll();
  set_cursor();
}

inline void print(const char *str, int color = LIGHT_GREY) {
  char *vga = (char *) 0xB8000;
  int i = 0;

  while (str[i] != '\0') {
    if (str[i] == '\n') {
      cursor_offset = (cursor_offset / 160 + 1) * 160;
      i++;
      continue;
    }
    if (str[i] == '\b') {
      cursor_offset = cursor_offset - 2;
      vga[cursor_offset] = 0;
      set_cursor();
      return;
    }
    vga[cursor_offset] = str[i];
    vga[cursor_offset + 1] = color;

    cursor_offset += 2;
    i++;

  }
  set_cursor();
  scroll();
}

inline void print_boot_info(const char *str) {
  print("[");
  print(" INFO ", CYAN);
  print("] ");
  print(str);
}

inline void print_boot_success(const char *str) {
  print("[");
  print(" OK ", GREEN);
  print("] ");
  print(str);
}

inline void print_boot_warn(const char *str) {
  print("[");
  print(" WARN ", YELLOW);
  print("] ");
  print(str);
}

inline void print_boot_error(const char *str) {
  print("[");
  print(" ERROR ", RED);
  print("] ");
  print(str);
}


inline void boot_banner() {
  print("NexOS kernel loaded successfully\n\n", LIGHT_GREEN);
  sleep_ms(300);
  print("Author: chri\n", LIGHT_CYAN);
  print("Contributors: none yet\n\n", LIGHT_CYAN);
}