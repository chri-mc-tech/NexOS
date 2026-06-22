#include "drivers/keyboard.hpp"
#include "pit.hpp"
#include "print.hpp"
#include "utils.hpp"

extern "C" void kernel_main() {
  boot_banner();

  keyboard_init();
  print_success("Initialized keyboard \n");


  while (1) {
    keyboard_buffer_update();

    print(keyboard_buffer);
  }
}

