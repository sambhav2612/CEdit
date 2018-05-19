void editorDrawRows(struct abuf *ab)
{
  int y;
  for (y = 0; y < E.screenRows; y++)
  {
    int filerow = y + E.rowoff;

    if (filerow >= E.numrows)
    {
      if (E.numrows == 0 && y == E.screenRows / 3)
      {
        char welcome[80];
        int welcomelen = snprintf(welcome, sizeof(welcome), "CEdit -- version %s", CEdit_VERSION);

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
    }
    else
    {
      int len = E.row[filerow].rsize - E.coloff;
      if (len < 0)
      {
        len = 0;
      }

      if (len > E.screenColumns)
      {
        len = E.screenColumns;
      }

      char *c = &E.row[filerow].render[E.coloff];
      unsigned char *hl = &E.row[filerow].hl[E.coloff];
      int current_color = -1;

      int j;
      for (j = 0; j < len; j++)
      {
        if (iscntrl(c[j]))
        {
          char sym = (c[j] <= 26) ? '@' + c[j] : '?';
          abAppend(ab, "\x1b[7m", 4);
          abAppend(ab, &sym, 1);
          abAppend(ab, "\x1b[m", 3);

          if (current_color != -1)
          {
            char buf[16];
            int clen = snprintf(buf, sizeof(buf), "\x1b[%dm", current_color);
            abAppend(ab, buf, clen);
          }
        }
        else if (hl[j] == HL_NORMAL)
        {
          if (current_color != -1)
          {
            abAppend(ab, "\x1b[39m", 5);
            current_color = -1;
          }
          abAppend(ab, &c[j], 1);
        }
        else
        {
          int color = editorSyntaxToColor(hl[j]);
          if (color != current_color)
          {
            current_color = color;
            char buf[16];

            // snprintf writes the escape sequence into buffer
            int clen = snprintf(buf, sizeof(buf), "\x1b[%dm", color);
            abAppend(ab, buf, clen);
          }
          abAppend(ab, &c[j], 1);
        }
      }
      abAppend(ab, "\x1b[39m", 5);
    }

    abAppend(ab, "\x1b[K", 3);
    abAppend(ab, "\r\n", 2);
  }
}

int editorRowCxToRx(erow *row, int cx)
{
  int rx = 0;
  int j;

  for (j = 0; j < cx; ++j)
  {
    if (row->chars[j] == '\t')
    {
      rx += (CEdit_TAB_STOP - 1) - (rx % CEdit_TAB_STOP);
    }
    rx++;
  }

  return rx;
}

int editorRowRxToCx(erow *row, int rx)
{
  int cur_rx = 0;
  int cx;

  for (cx = 0; cx < row->size; cx++)
  {
    if (row->chars[cx] == '\t')
    {
      cur_rx += (CEdit_TAB_STOP - 1) - (cur_rx % CEdit_TAB_STOP);
    }
    cur_rx++;

    if (cur_rx > rx)
    {
      return cx;
    }

    return cx;
  }
}

void editorUpdateRow(erow *row)
{
  int tabs = 0;
  int j;

  for (j = 0; j < row->size; ++j)
  {
    if (row->chars[j] == '\t')
    {
      tabs++;
    }
  }

  free(row->render);
  row->render = malloc(row->size + tabs * (CEdit_TAB_STOP - 1) + 1);

  int index = 0;
  for (j = 0; j < row->size; ++j)
  {
    if (row->chars[j] == '\t')
    {
      row->render[index++] = ' ';

      while (index % CEdit_TAB_STOP != 0)
      {
        row->render[index++] == ' ';
      }
    }
    else
    {
      row->render[index++] = row->chars[j];
    }
  }

  row->render[index] = '\0';
  row->rsize = index;

  editorUpdateSyntax(row);
}

void editorInsertRow(int at, char *s, size_t len)
{
  if (at < 0 || at > E.numrows)
  {
    return;
  }

  E.row = realloc(E.row, sizeof(erow) * (E.numrows + 1));
  memmove(&E.row[at + 1], &E.row[at], sizeof(erow) * (E.numrows - at));

  int j;
  for (j = at + 1; j <= E.numrows; j++)
    E.row[j].idx++;

  E.row[at].idx = at;

  E.row[at].size = len;
  E.row[at].chars = malloc(len + 1);

  memcpy(E.row[at].chars, s, len);

  E.row[at].chars[len] = '\0';
  E.row[at].rsize = 0;
  E.row[at].render = NULL;
  E.row[at].hl = NULL;
  E.row[at].hl_open_comment = 0;

  editorUpdateRow(&E.row[at]);

  E.numrows++;
  E.dirty++;
}

void editorFreeRow(erow *row)
{
  free(row->render);
  free(row->chars);
  free(row->hl);
}

void editorDelRow(int at)
{
  if (at < 0 || at >= E.numrows)
  {
    return;
  }

  editorFreeRow(&E.row[at]);
  memmove(&E.row[at], &E.row[at + 1], sizeof(erow) * (E.numrows - at - 1));

  int j;
  for (j = at; j < E.numrows - 1; j++)
    E.row[j].idx--;

  E.numrows--;
  E.dirty++;
}

void editorRowInsertChar(erow *row, int at, int c)
{
  if (at < 0 || at > row->size)
  {
    at = row->size;
  }

  row->chars = realloc(row->chars, row->size + 2);
  memmove(&row->chars[at + 1], &row->chars[at], row->size - at + 1);
  row->size++;
  row->chars[at] = c;

  editorUpdateRow(row);
  E.dirty++;
}

void editorRowAppendString(erow *row, char *s, size_t len)
{
  row->chars = realloc(row->chars, row->size + len + 1);
  memcpy(&row->chars[row->size], s, len);

  row->size += len;
  row->chars[row->size] = '\0';

  editorUpdateRow(row);
  E.dirty++;
}

void editorRowDelChar(erow *row, int at)
{
  if (at < 0 || at >= row->size)
  {
    return;
  }

  memmove(&row->chars[at], &row->chars[at + 1], row->size - at);
  row->size--;
  editorUpdateRow(row);
  E.dirty++;
}

void editorInsertChar(int c)
{
  if (E.cy == E.numrows)
  {
    editorInsertRow(E.numrows, "", 0);
  }

  editorRowInsertChar(&E.row[E.cy], E.cx, c);
  E.cx++;
}

void editorInsertNewline()
{
  if (E.cx == 0)
  {
    editorInsertRow(E.cy, "", 0);
  }
  else
  {
    erow *row = &E.row[E.cy];
    editorInsertRow(E.cy + 1, &row->chars[E.cx], row->size - E.cx);

    row = &E.row[E.cy];
    row->size = E.cx;
    row->chars[row->size] = '\0';

    editorUpdateRow(row);
  }

  E.cy++;
  E.cx = 0;
}

void editorDelChar()
{
  if (E.cy == E.numrows)
  {
    return;
  }

  if (E.cx == 0 && E.cy == 0)
  {
    return;
  }

  erow *row = &E.row[E.cy];
  if (E.cx > 0)
  {
    editorRowDelChar(row, E.cx - 1);
    E.cx--;
  }
  else
  {
    E.cx = E.row[E.cy - 1].size;
    editorRowAppendString(&E.row[E.cy - 1], row->chars, row->size);
    editorDelRow(E.cy);

    E.cy--;
  }
}

void editorScroll()
{
  E.rx = 0;
  if (E.cy < E.numrows)
  {
    E.rx = editorRowCxToRx(&E.row[E.cy], E.cx);
  }

  if (E.cy < E.rowoff)
  {
    E.rowoff = E.cy;
  }

  if (E.cy >= E.rowoff + E.screenRows)
  {
    E.rowoff = E.cy - E.screenRows + 1;
  }

  if (E.rx < E.coloff)
  {
    E.coloff = E.rx;
  }

  if (E.rx >= E.coloff + E.screenColumns)
  {
    E.coloff = E.rx - E.screenColumns + 1;
  }
}

void editorDrawStatusBar(struct abuf *ab)
{
  abAppend(ab, "\x1b[7m", 4);

  char status[80], rstatus[80];
  int len = snprintf(status, sizeof(status), "%.20s - %d lines %s",
                     E.filename ? E.filename : "[No Name]", E.numrows,
                     E.dirty ? "(modified)" : "");

  int rlen = snprintf(rstatus, sizeof(rstatus), "%s | %d/%d",
                      E.syntax ? E.syntax->filetype : "no ft",
                      E.cy + 1, E.numrows);

  if (len > E.screenColumns)
  {
    len = E.screenColumns;
  }

  abAppend(ab, status, len);

  while (len < E.screenColumns)
  {
    if (E.screenColumns - len == rlen)
    {
      abAppend(ab, rstatus, rlen);
      break;
    }
    else
    {
      abAppend(ab, " ", 1);
      len++;
    }
  }

  abAppend(ab, "\x1b[m", 3);
  abAppend(ab, "\r\n", 2);
}

void editorSetStatusMessage(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);

  vsnprintf(E.statusmsg, sizeof(E.statusmsg), fmt, ap);

  va_end(ap);
  E.statusmsg_time = time(NULL);
}

void editorDrawMessageBar(struct abuf *ab)
{
  abAppend(ab, "\x1b[K", 3);

  int msglen = strlen(E.statusmsg);
  if (msglen > E.screenColumns)
  {
    msglen = E.screenColumns;
  }

  if (msglen && time(NULL) - E.statusmsg_time < 5)
  {
    abAppend(ab, E.statusmsg, msglen);
  }
}