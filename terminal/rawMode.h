void initEditor()
{
    E.cx = 0;
    E.cy = 0;
    E.rowoff = 0;
    E.numrows = 0;
    E.row = NULL;

    if (getWindowSize(&E.screenRows, &E.screenColumns) == -1)
        die("getWindowSize");
}

// turns on the display of what is being typed
void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
        die("tcsetattr");
}

// shuts off the display of what is being typed
void switchToRawMode()
{
    if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1)
        die("tcgetattr");

    atexit(disableRawMode);

    struct termios raw = E.orig_termios;

    // c_oflag refers to output flags
    raw.c_oflag &= ~(OPOST); // trun off output processing

    // c_iflag refers to input flags
    raw.c_iflag &= ~(IXON);   // disable ctrl-s ctrl-q
    raw.c_iflag &= ~(ICRNL);  // carriage return newline
    raw.c_iflag &= ~(BRKINT); // break condition
    raw.c_iflag &= ~(INPCK);  // enable parity check
    raw.c_iflag &= ~(ISTRIP); // strip every 8th bit of input

    // c_lflag refers to local flags
    raw.c_lflag &= ~(ICANON); // trurn off canonical mode
    raw.c_lflag &= ~(ECHO);   // turn off echoing
    raw.c_lflag &= ~(ISIG);   // disable ctrl-c ctrl-z
    raw.c_lflag &= ~(IEXTEN); // disable ctrl-v

    // c_oflag refers to local flags
    raw.c_cflag |= (CS8); // bit mask

    // c.cc stand for control characters
    raw.c_cc[VMIN] = 0;   // minmium number of input bytes
    raw.c_cc[VTIME] = 1; // (one second) max amount of time to wait before read() returns

    // TCSAFLUSH argument specifies when to apply the change
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}