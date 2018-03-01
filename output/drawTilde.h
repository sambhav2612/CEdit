void editorDrawRows(struct abuf *ab)
{
  int y;
  for (y = 0; y < E.screenRows; y++)
  {
    if (y >= E.screenRows) {
    if (E.screenRows == 0 && y == E.screenRows / 3)
    {
      char welcome[80];
      int welcomelen = snprintf(welcome, sizeof(welcome), "textC editor -- version %s", KILO_VERSION);

      if (welcomelen > E.screenColumns)
        welcomelen = E.screenColumns;

      int padding = (E.screenColumns - welcomelen) / 2;

      if (padding)
      {
        abAppend(ab, "~", 1);
        padding--;
      }

      while (padding--)
        abAppend(ab, " ", 1);

      abAppend(ab, welcome, welcomelen);
    }
    else
    {
      abAppend(ab, "~", 1);
    }
  } else {
      int len = E.row[y].size;
      if (len > E.screenColumns)
        len = E.screenColumns;
      abAppend(ab, E.row[y].chars, len);
  }

    abAppend(ab, "\x1b[K", 3);

    if (y < E.screenRows - 1)
    {
      abAppend(ab, "\r\n", 2);
    }
  }
}

void editorAppendRow(char *s, size_t len) {
  E.row = realloc(E.row, sizeof(erow) * (E.numrows+1));
  
  int at = E.numrows;
  E.row[at].size = len;
  E.row[at].chars = malloc(len + 1);
  
  memcpy(E.row[at].chars, s, len);
  
  E.row[at].chars[len] = '\0';
  E.numrows++;
}