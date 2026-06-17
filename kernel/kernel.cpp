extern "C" void kernel_main() {
  char *video_memory = (char *) (0xB8000 + 320);
  video_memory[0] = 'H';
  video_memory[1] = 0x0F;
  video_memory[2] = 'i';
  video_memory[3] = 0x0F;
  while (1)
    ;
}

