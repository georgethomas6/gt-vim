
#include <termios.h>
#include <unistd.h>

#define RESET_CURSOR "\033[H" // moves cursor to home position(0, 0)
#define CLEAR "\033[H"        // clears the screen

void enable_raw_mode(void);
void disable_raw_mode(struct termios *);

/*
ESC[{line};{column}H
ESC[{line};{column}f 	moves cursor to line #, column #
ESC[#A 	moves cursor up # lines
ESC[#B 	moves cursor down # lines
ESC[#C 	moves cursor right # columns
ESC[#D 	moves cursor left # columns
ESC[#E 	moves cursor to beginning of next line, # lines down
ESC[#F 	moves cursor to beginning of previous line, # lines up
ESC[#G 	moves cursor to column #
ESC[6n 	request cursor position (reports as ESC[#;#R)
ESC M 	moves cursor one line up, scrolling if needed
ESC 7 	save cursor position (DEC)
ESC 8 	restores the cursor to the last saved position (DEC)
ESC[s 	save cursor position (SCO)
ESC[u 	restores the cursor to the last saved position (SCO)
*/
