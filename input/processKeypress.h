void editorMoveCursor(char key) {
    switch(key) {
        case 'w':
            E.cx++;
            break;

        case 'a' :
            E.cx--;
            break;
        
        case 's': 
            E.cy++;
            break;

        case 'd': 
            E.cy--;
            break;
    }
}

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

    case 'w':
    case 'a':
    case 's':
    case 'd':
        editorMoveCursor(c);
        break;
    }
}
