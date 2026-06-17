
#include "../include/terminal_commands.h"

/*
 * This function modifies the current terminal settings to enable raw mode
 * */
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

/*
 * This function is a wrapper around tcsetattr to change the state of the
 * terminal.
 * */
void disable_raw_mode(struct termios *original) {
  tcsetattr(STDIN_FILENO, TCSANOW, original);
}
