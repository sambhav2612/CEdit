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
#include <time.h>
#include <stdarg.h>
#include <fcntl.h>

// local headers
#include "globals.h"
#include "terminal/die.h"
#include "terminal/getWindowSize.h"
#include "terminal/rawMode.h"
#include "terminal/readKeypress.h"
#include "buffer/mutableString.h"
#include "output/drawTilde.h"
#include "output/refreshScreen.h"
#include "io/fileIO.h"
#include "io/editorOpen.h"
#include "input/processKeypress.h"
#include "input/prompter.h"

// driver functions
int main(int argc, char *argv[])
{
    switchToRawMode();
    initEditor();

    if (argc >= 2)
    {
        editorOpen(argv[1]);
    }

    editorSetStatusMessage("HELP: Ctrl-S = Save | Ctrl-Q = Quit | Ctrl-F = Search");

    while (1)
    {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}
