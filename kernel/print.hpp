#pragma once
#include <cstring>

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

int cursor_offset = 320;

inline void scroll() {
  char *vga = (char *) 0xB8000;
  if (cursor_offset >= 4000) {
    for (int i = 0; i < 4000; i++) {
      vga[i] = vga[i + 320];
    }
  }
}

inline void print(const char *str, int color = WHITE) {
  char *vga = (char *) 0xB8000;
  int i = 0;

  while (str[i] != '\0') {
    if (str[i] == '\n') {
      cursor_offset = (cursor_offset / 160 + 1) * 160;
      i++;
      continue;
    }
    vga[cursor_offset] = str[i];
    vga[cursor_offset + 1] = color;

    cursor_offset += 2;
    i++;

  }
  scroll();
}

inline void print_success(const char *str) {
  print("[");
  print(" OK ", GREEN);
  print("] ");
  print(str);
}

inline void print_warn(const char *str) {
  print("[");
  print(" WARN ", YELLOW);
  print("] ");
  print(str);
}

inline void print_error(const char *str) {
  print("[");
  print(" ERROR ", RED);
  print("] ");
  print(str);
}
