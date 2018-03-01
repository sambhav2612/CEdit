#define KILO_VERSION "0.0.4"
#define ABUF_INIT {NULL, 0}
#define CTRL_KEY(k) ((k)&0x1f)

enum editorKey {
  ARROW_LEFT = 'a',
  ARROW_RIGHT = 'd',
  ARROW_UP = 'w',
  ARROW_DOWN = 's'
};

struct abuf
{
    char *b;
    int len;
};

// global variable to store default terminal attribute
struct editorConfig
{
    int cx, cy;

    int screenRows;
    int screenColumns;

    struct termios orig_termios;
} E;