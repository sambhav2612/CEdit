#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#include "rawMode.h"

int main()
{

    switchToRawMode();

    while (1)
    {
        char ch = '\0';
        if (read(STDIN_FILENO, &ch, 1) == -1 && errno != EAGAIN)
            die("read");

        if (iscntrl(ch))
        {
            printf("%d\r\n", ch);
        }
        else
        {
            printf("%d ('%c')\r\n", ch, ch);
        }
        if (ch == 'q')
            break;
    }

    return 0;
}