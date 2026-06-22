#include "drivers/keyboard.hpp"
#include "pit.hpp"
#include "print.hpp"
#include "utils.hpp"

extern "C" [[noreturn]] void kernel_main() {
  boot_banner();
  keyboard_init();

  print("NexOS: ");

  while (true) {
    keyboard_buffer_update();
    keyboard_print();

  }
}

