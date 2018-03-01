void editorMoveCursor(int key) {
    switch(key) {
        case ARROW_UP:
            E.cx++;
            break;

        case ARROW_LEFT:
            E.cx--;
            break;
        
        case ARROW_DOWN: 
            E.cy++;
            break;

        case ARROW_RIGHT: 
            E.cy--;
            break;
    }
}

void editorProcessKeypress()
{
    int c = editorReadKey();
    // printf("%d\r\n", c); => works on exit
    switch (c)
    {
    case CTRL_KEY('q'):
        write(STDOUT_FILENO, "\x1b[2J", 4);
        write(STDOUT_FILENO, "\x1b[H", 3);

        exit(0);
        break;

    case ARROW_UP:
    case ARROW_LEFT:
    case ARROW_DOWN:
    case ARROW_RIGHT:
        editorMoveCursor(c);
        break;
    }
}
