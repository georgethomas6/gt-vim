#include "../include/input.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  struct termios orig;
  // STDIN_FILENO is this fd generally refer to the terminal
  tcgetattr(STDIN_FILENO, &orig);

  enable_raw_mode();
  char c = 0;
  while (read(STDIN_FILENO, &c, 1) > 0 && c != 'q') {
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
  }
  disable_raw_mode(&orig);
  return EXIT_SUCCESS;
}
