// includes

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

// modular headers :wink:
#include "sub-headers/rawMode.h"
#include "sub-headers/refreshScreen.h"

#define CTRL_KEY(k) ((k)&0x1f)

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
        write(STDOUT_FILENO, "\x1b[2J", 4);
        write(STDOUT_FILENO, "\x1b[H", 3);
        
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