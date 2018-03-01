// includes

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <string.h>

// modular headers :wink:
#include "globals.h"
#include "terminal/die.h"
#include "terminal/getWindowSize.h"
#include "terminal/rawMode.h"
#include "terminal/readKeypress.h"
#include "buffer/mutableString.h"
#include "output/drawTilde.h"
#include "output/refreshScreen.h"
#include "input/processKeypress.h"
#include "io/editorOpen.h"

// driver functions
int main()
{
    switchToRawMode();
    initEditor();
    editorOpen();

    while (1)
    {
        editorRefreshScreen();
        editorProcessKeypress();
    }
    return 0;
}
