int cursor_offset = 320;

void print(const char* str);

extern "C" void kernel_main() {

  print("NexOS kernel loaded successfully\n");

  while (1);
}

void print(const char* str) {
  char* vga = (char*)0xB8000;
  int i = 0;

  while (str[i] != '\0') {
    if (str[i] == '\n') {
      cursor_offset = (cursor_offset / 160 + 1) * 160;
      i++;
      continue;
    }
    vga[cursor_offset] = str[i];
    vga[cursor_offset + 1] = 0x0F;

    cursor_offset += 2;
    i++;
  }
}