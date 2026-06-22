#include "pit.hpp"
#include "print.hpp"
#include "utils.hpp"

extern "C" void kernel_main() {
  boot_banner();

  print_success("test success \n");
  print_warn("test warn \n");

  while (1);
}