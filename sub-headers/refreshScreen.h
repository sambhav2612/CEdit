void editorRefreshScreen()
{
    struct abuf ab = ABUF_INIT;

    abAppend(ab, "\x1b[?25l", 6);
    // abAppend(ab, "\x1b[2J", 4);
    abAppend(ab, "\x1b[H", 3);

    editorDrawRows(&ab);

    abAppend(ab, "\x1b[H", 3);
    abAppend(ab, "\x1b[25h", 6);

    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}