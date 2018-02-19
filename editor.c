// includes

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>

// modular headers :wink:
#include "globals.h"
#include "terminal/rawMode.h"
#include "terminal/readKeypress.h"
#include "terminal/die.h"
#include "terminal/getWindowSize.h"
#include "output/refreshScreen.h"
#include "output/drawTilde.h"
#include "input/processKeypress.h"
#include "buffer/mutableString.h"

// driver functions
int main()
{
    switchToRawMode();
    initEditor();
    while (1)
    {
        editorRefreshScreen();
        editorProcessKeypress();
    }
    return 0;
}