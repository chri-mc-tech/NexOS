#pragma once
#include "../utils.hpp"

inline void command_handler(const char* command) {
  if (are_string_equals(command, "help")) {
    print("commands:\n");
    print("- help\n");
    print("- test\n");
  }
  else if (are_string_equals(command, "test")) {
    print("test\n");
  }
  else if (are_string_equals(command, "")) {
    return;
  }
  else {
    print("ERROR: ", RED);
    print("command not found: ");
    print(command);
    print("\n");
    print("Type \"help\" for the list of available commands\n");

  }
}