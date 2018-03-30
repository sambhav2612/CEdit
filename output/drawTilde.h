void editorDrawRows(struct abuf *ab)
{
  int y;
  for (y = 0; y < E.screenRows; y++) {
    int filerow = y + E.rowoff; 

    if (filerow >= E.numrows) {
      if (E.numrows == 0 && y == E.screenRows / 3)
      {
        char welcome[80];
        int welcomelen = snprintf(welcome, sizeof(welcome), "textC editor -- version %s", TEXTC_VERSION);

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
        int len = E.row[filerow].rsize - E.coloff;
        if (len < 0) {
          len = 0;
        }
        
        if (len > E.screenColumns) {
          len = E.screenColumns;
        }
        abAppend(ab, &E.row[filerow].render[E.coloff], len);
    }

    abAppend(ab, "\x1b[K", 3);

    //if (y < E.screenRows - 1) {
      abAppend(ab, "\r\n", 2);
    //}
  }
}

int editorRowCxToRx(erow *row, int cx) {
  int rx = 0;
  int j;

  for (j = 0; j < cx; ++j) {
    if (row->chars[j] == '\t') {
      rx += (TEXTC_TAB_STOP - 1) - (rx % TEXTC_TAB_STOP);
    }
    rx++;
  }

  return rx;
}

void editorUpdateRow(erow *row) {
  int tabs = 0;
  int j;

  for (j = 0; j < row->size; ++j) {
    if (row->chars[j] == '\t') {
      tabs++;
    }
  }
  
  free(row->render);
  row->render = malloc(row->size + tabs*(TEXTC_TAB_STOP - 1) + 1);

  int index = 0;
  for (j = 0; j < row->size; ++j) {
    if (row->chars[j] == '\t') {
      row->render[index++] = ' ';
      
      while (index % TEXTC_TAB_STOP != 0) {
        row->render[index++] == ' ';
      }
    } else {
      row->render[index++] = row->chars[j];
    }
  }

  row->render[index] = '\0';
  row->rsize = index;
}

void editorAppendRow(char *s, size_t len) {
  E.row = realloc(E.row, sizeof(erow) * (E.numrows+1));
  
  int at = E.numrows;
  E.row[at].size = len;
  E.row[at].chars = malloc(len + 1);
  
  memcpy(E.row[at].chars, s, len);
  
  E.row[at].chars[len] = '\0';
  E.row[at].rsize = 0;
  E.row[at].render = NULL;

  editorUpdateRow(&E.row[at]);

  E.numrows++;
}

void editorRowInsertChar(erow *row, int at, int c) {
  if (at < 0 || at > row->size) {
    at = row->size;
  }

  row->chars = realloc(row->chars, row->size + 2);
  memmove(&row->chars[at+1], &row->chars[at], row->size-at+1);
  row->size++;
  row->chars[at] = c;

  editorUpdateRow(row);
}

void editorInsertChar(int c) {
  if (E.cy == E.numrows) {
    editorAppendRow("", 0);
  }
  
  editorRowInsertChar(&E.row[E.cy], E.cx, c);
  E.cx++;
}

void editorScroll() {
  E.rx = 0;
  if (E.cy < E.numrows) {
    E.rx = editorRowCxToRx(&E.row[E.cy], E.cx);
  }

  if (E.cy < E.rowoff) {
    E.rowoff = E.cy;
  }

  if (E.cy >= E.rowoff + E.screenRows) {
    E.rowoff = E.cy - E.screenRows + 1;
  }

  if (E.rx < E.coloff) {
    E.coloff = E.rx;
  }

  if (E.rx >= E.coloff + E.screenColumns) {
    E.coloff = E.rx - E.screenColumns + 1;
  }
}

void editorDrawStatusBar(struct abuf *ab) {
  abAppend(ab, "\x1b[7m", 4);
  
  char status[80], rstatus[80]; 
  int len = snprintf(status, sizeof(status), "%.20s - %d lines", 
                      E.filename ? E.filename : "[No Name]", E.numrows);

  int rlen = snprintf(rstatus, sizeof(rstatus), "%d/%d",
                      E.cy + 1, E.numrows);

  if (len > E.screenColumns) {
    len = E.screenColumns;
  }

  abAppend(ab, status, len);

  while(len < E.screenColumns) {
    if (E.screenColumns - len == rlen) {
      abAppend(ab, rstatus, rlen);
      break;
    } else {
      abAppend(ab, " ", 1);
      len++;
    }
  }

  abAppend(ab, "\x1b[m", 3);
  abAppend(ab, "\r\n", 2);
}

void editorSetStatusMessage(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  vsnprintf(E.statusmsg, sizeof(E.statusmsg), fmt, ap);
  
  va_end(ap);
  E.statusmsg_time = time(NULL);
}

void editorDrawMessageBar(struct abuf *ab) {
  abAppend(ab, "\x1b[K", 3);

  int msglen = strlen(E.statusmsg);
  if (msglen > E.screenColumns) {
    msglen = E.screenColumns;
  }

  if (msglen && time(NULL) - E.statusmsg_time < 5) {
    abAppend(ab, E.statusmsg, msglen);
  }
}