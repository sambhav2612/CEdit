int editorReadKey()
{
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
    {
        if (nread == -1 && errno != EAGAIN)
            die("read");
    }

    if (c == '\x1b') {
        char seq[3];

        if (read(STDIN_FILENO, &seq[0], 1) != 1)
            return '\x1b';

        if (read(STDIN_FILENO, &seq[1], 1) != 1)
            return '\x1b';       

        if (seq[0] == '[') {
            switch (seq[0]) {
                case 'A': return ARROW_UP;
                case 'B': return ARROW_LEFT;
                case 'C': return ARROW_DOWN;
                case 'D': return ARROW_RIGHT;
            }

            return '\x1b';
        } else {
            return c;
        }
    }

    return c;
}