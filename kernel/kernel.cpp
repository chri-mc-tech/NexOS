#include "print.hpp"
#include "utils.hpp"

extern "C" void kernel_main() {

  print("[kernel] NexOS kernel loaded successfully\n\n", GREEN);

  print_success("test success \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");
  print_warn("test warn \n");

  print_success(int_to_string(cursor_offset));

  while (1);
}
