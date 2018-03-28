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

    if (y < E.screenRows - 1)
    {
      abAppend(ab, "\r\n", 2);
    }
  }
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

void editorScroll() {
  E.rx = E.cx;

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