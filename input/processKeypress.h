void editorMoveCursor(int key) {
  erow *row = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];

  switch (key) {
    case ARROW_LEFT:
      if (E.cx != 0) {
        E.cx--;
      } else if (E.cy > 0) {
        E.cy--;
        E.cx = E.row[E.cy].size;
      }
      break;
    case ARROW_RIGHT:
      if (row && E.cx < row->size) {
        E.cx++;
      } else if (row && E.cx == row->size) {
        E.cy++;
        E.cx = 0;
      }
      break;
    case ARROW_UP:
      if (E.cy != 0) {
        E.cy--;
      }
      break;
    case ARROW_DOWN:
      if (E.cy < E.numrows) {
        E.cy++;
      }
      break;
  }

  row = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];
  int rowlen = row ? row->size : 0;
  if (E.cx > rowlen) {
    E.cx = rowlen;
  }
}

void editorProcessKeypress()
{
    int c = editorReadKey();
    switch (c)
    {
      case '\r':
        break;

      case CTRL_KEY('q'):
        write(STDOUT_FILENO, "\x1b[2J", 4);
        write(STDOUT_FILENO, "\x1b[H", 3);

        exit(0);
        break;

      case CTRL_KEY('s'):
        editorSave();
        break;

      case HOME_KEY:
        E.cx = 0;
        break;
        
      case END_KEY:
        if (E.cy < E.numrows) {
            E.cx = E.row[E.cy].size;
        }
        break;
      
      case BACKSPACE:
      case CTRL_KEY('h'):
      case DEL_KEY:
        break;

      case PAGE_UP:
      case PAGE_DOWN:
        {
            if (c == PAGE_UP) {
                E.cy = E.rowoff;
            } else if (c == PAGE_DOWN) {
                E.cy = E.rowoff + E.screenRows - 1;
                if (E.cy > E.numrows) {
                    E.cy = E.numrows;
                }
            }
            
            int times = E.screenRows;
            while (times--)
                editorMoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
        }
        break;

      case ARROW_UP:
      case ARROW_LEFT:
      case ARROW_DOWN:
      case ARROW_RIGHT:
        editorMoveCursor(c);
        break;

      case CTRL_KEY('l'):
      case '\x1b':
        break;
    
      default:
      editorInsertChar(c);
      break;
    
    }
}
