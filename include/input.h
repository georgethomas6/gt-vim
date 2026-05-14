
#include <termios.h>
#include <unistd.h>

void enable_raw_mode(void);
void disable_raw_mode(struct termios *);
