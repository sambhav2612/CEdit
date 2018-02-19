void editorDrawRows(struct abuf *ab)
{
  int y;
  for (y = 0; y < E.screenRows; y++)
  {
    if (y == E.screenRows / 3)
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

    abAppend(ab, "\x1b[K", 3);

    if (y < E.screenRows - 1)
    {
      abAppend(ab, "\r\n", 2);
    }
  }
}