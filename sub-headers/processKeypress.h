#define CTRL_KEY(k) ((k)&0x1f)

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
