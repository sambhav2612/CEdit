void editorOpen() {
    char *line = "Hello, world!";
    ssize_t linelen = 13;
    
    E.row.size = linelen;
    E.row.chars = malloc(linelen + 1);
    
    memcpy(E.row.chars, line, linelen);
    
    E.row.chars[linelen] = '\0';
    E.numrows = 1;
}