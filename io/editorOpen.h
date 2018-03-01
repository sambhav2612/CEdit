void editorOpen(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        die("fopen");
    }

    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;

    linelen = getline(&line, &linecap, fp);

    if ((linelen = getline(&line, &linecap, fp)) != -1) {
        while (linelen > 0 && line[linelen-1] == '\n' || line[linelen-1] == '\r') {
            linelen--;
        }

        editorAppendRow(line, linelen);
    }

    free(line);
    fclose(fp);
}