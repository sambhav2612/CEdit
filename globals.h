#define TEXTC_VERSION "0.0.6"
#define TEXTC_TAB_STOP 8
#define ABUF_INIT {NULL, 0}
#define CTRL_KEY(k) ((k)&0x1f)

#define _BSD_SOURCE
#define _GNU_SOURCE

enum editorKey {
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN,
  DEL_KEY,
  HOME_KEY,
  END_KEY,
  PAGE_UP,
  PAGE_DOWN
};

struct abuf
{
    char *b;
    int len;
};

typedef struct erow {
  int size;
  int rsize;
  char *chars;
  char *render;
} erow;

// global variable to store default terminal attribute
struct editorConfig
{
    int cx, cy;
    int rowoff;
    int coloff;
    int screenRows;
    int screenColumns;
    int numrows;
    erow *row;

    struct termios orig_termios;
} E;