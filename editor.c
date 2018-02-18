#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>

// global variable to store default terminal attribute
struct termios orig_termios;

// turns on the display of what is being typed
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

// shuts off the display of what is being typed
void switchToRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    // c_lflag refers to local flags, ECHO is a bitflag
    raw.c_lflag &= ~(ICANON);
    raw.c_lflag &= ~(ECHO);
    // TCSAFLUSH argument specifies when to apply the change
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {

    switchToRawMode();

    char ch;
    while (read (STDIN_FILENO, &ch, 1) == 1 && (ch != 'q')) {
        if (iscntrl (ch)) {
            printf("%d\n", ch);
        } else {
            printf("%d ('%c')\n", ch, ch);    
        }
    }

    return 0;
}