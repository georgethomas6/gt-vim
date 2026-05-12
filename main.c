#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

void handle_sigint(int sig);

void enable_raw_mode(void);
void disable_raw_mode(struct termios *);

int main(int argc, char *argv[]) {

  struct termios orig;
  // STDIN_FILENO is this fd generally refer to the terminal
  tcgetattr(STDIN_FILENO, &orig);

  enable_raw_mode();
  char c = 0;
  while (read(STDIN_FILENO, &c, 1) >= 0 && c != 'q') {
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
  }
  disable_raw_mode(&orig);
  return EXIT_SUCCESS;
}

void enable_raw_mode(void) {
  struct termios raw;
  tcgetattr(STDIN_FILENO, &raw);

  // IXON -- disables ^s and ^q signals
  // BRKINT, INPCK, ISTRIP are unimportant
  // ICRNL maps CR to NL
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  // ~OPOST turns off all output processing
  raw.c_oflag &= ~(OPOST);

  raw.c_cflag |= (CS8);
  // ~ECHO -> turns off echoing input keys
  // ~ISIG -> turns off sending ^c, ^z
  // ~ICONAN -> turns off canonical mode and allows input to be read byte by
  // byte
  // ~IEXTEN -> stops the terminal driver from acting on "extended" control
  // characters
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void disable_raw_mode(struct termios *original) {
  tcsetattr(STDIN_FILENO, TCSANOW, original);
}
