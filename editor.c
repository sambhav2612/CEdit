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
#include "sub-headers/processKeypress.h"

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