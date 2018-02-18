// includes

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

// modular headers :wink:
#include "sub-headers/rawMode.h"

#define CTRL_KEY(k) ((k)&0x1f)

void editorRefreshScreen()
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
}

char editorReadKey()
{
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
    {
        if (nread == -1 && errno != EAGAIN)
            die("read");
    }
    return c;
}

void editorProcessKeypress()
{
    char c = editorReadKey();
    // printf("%d\r\n", c); => works on exit
    switch (c)
    {
    case CTRL_KEY('q'):
        exit(0);
        break;

    }

}

// driver functions
int main()
{
    switchToRawMode();
    while (1)
    {
        editorRefreshScreen();
        editorProcessKeypress();
    }
    return 0;
}