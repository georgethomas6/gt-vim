#include "../include/terminal_commands.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
int main(int argc, char *argv[]) {

  struct winsize win;
  struct termios orig;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
  // STDIN_FILENO is this fd generally refer to the terminal
  tcgetattr(STDIN_FILENO, &orig);

  enable_raw_mode();
  char c = 0;
  while (read(STDIN_FILENO, &c, 1) > 0 && c != 'q') {
    if (c == 'c') {
      if (write(STDIN_FILENO, "\033[H\033[2J", strlen("\033[H\033[2J")) <
          0) { // clears screen
        break;
      };
    } else if (c == 'j') {
      write(STDIN_FILENO, "\033D", strlen("\033D")); // scrolls down one
    } else if (c == 'k') {

      write(STDIN_FILENO, "\033M", strlen("\033D")); // scrolls up one
    } else if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      for (int i = 0; i < 50; i++) {
        printf("%d ('%c')\r\n", c, c);
      }
      for (int i = 0; i < 30; i++) {
        printf("%d ('%c')\r\n", c + 1, c + 1);
      }
    }
  }

  printf("\033[H\033[2J");
  disable_raw_mode(&orig);
  return EXIT_SUCCESS;
}
