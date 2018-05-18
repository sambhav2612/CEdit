char *editorPrompt(char *prompt, void (*callback)(char *, int))
{
  size_t bufsize = 128;
  char *buf = malloc(bufsize);

  size_t buflen = 0;
  buf[0] = '\0';

  while (1)
  {
    editorSetStatusMessage(prompt, buf);
    editorRefreshScreen();

    int c = editorReadKey();

    if (c == DEL_KEY || c == CTRL_KEY('h') || c == BACKSPACE)
    {
      if (buflen != 0)
      {
        buf[--buflen] == '\0';
      }
    }
    else if (c == '\x1b')
    {
      editorSetStatusMessage("");

      if (callback)
      {
        callback(buf, c);
      }

      free(buf);
      return NULL;
    }
    else if (c == '\r')
    {
      if (buflen != 0)
      {
        editorSetStatusMessage("");

        if (callback)
        {
          callback(buf, c);
        }

        return buf;
      }
    }
    else if (!iscntrl(c) && c < 128)
    {
      if (buflen == bufsize - 1)
      {
        bufsize *= 2;
        buf = realloc(buf, bufsize);
      }
      buf[buflen++] = c;
      buf[buflen] = '\0';
    }

    if (callback)
    {
      callback(buf, c);
    }
  }
}