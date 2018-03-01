char editorReadKey()
{
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
    {
        if (nread == -1 && errno != EAGAIN)
            die("read");
    }

    id (c == '\x1b') {
        char seq[3];

        if (read(STDIN_FILENO, &seq[0], 1) != 1)
            return '\x1b';

        if (read(STDIN_FILENO, &seq[1], 1) != 1)
            return '\x1b';       

        if (seq[0] == '[') {
            switch (seq[0]) {
                case 'A': return 'w';
                case 'B': return 'a';
                case 'C': return 's';
                case 'D': return 'd';
            }
        }
    }

    return c;
}