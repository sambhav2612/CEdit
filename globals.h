#define CEdit_VERSION "0.0.10"
#define CEdit_TAB_STOP 8
#define CEdit_QUIT_TIMES 3

#define ABUF_INIT \
  {               \
    NULL, 0       \
  }
#define CTRL_KEY(k) ((k)&0x1f)

#define _BSD_SOURCE
#define _GNU_SOURCE

#define HL_HIGHLIGHT_NUMBERS (1 << 0)
#define HL_HIGHLIGHT_STRINGS (1 << 1)

enum editorKey
{
  BACKSPACE = 127,
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

enum editorHighlight
{
  HL_NORMAL = 0,
  HL_MLCOMMENT,
  HL_COMMENT,
  HL_KEYWORD1,
  HL_KEYWORD2,
  HL_STRING,
  HL_NUMBER,
  HL_MATCH
};

struct abuf
{
  char *b;
  int len;
};

struct editorSyntax
{
  char *filetype;
  char **filematch;
  char **keywords;
  char *single_line_comments;
  char *multiline_comment_start;
  char *multiline_comment_end;

  int flags;
};

typedef struct erow
{
  int idx;
  int size;
  int rsize;
  char *chars;
  char *render;
  unsigned char *hl;
  int hl_open_comment;
} erow;

// global variable to store default terminal attribute
struct editorConfig
{
  int cx, cy;
  int rx;
  int rowoff;
  int coloff;
  int screenRows;
  int screenColumns;
  int numrows;
  erow *row;
  int dirty;
  char *filename;
  char statusmsg[80];
  time_t statusmsg_time;
  struct editorSyntax *syntax;
  struct termios orig_termios;
} E;

char *C_HL_extensions[] = {".c", ".h", NULL};
char *C_HL_keywords[] = {
    "switch", "if", "while", "for", "break", "continue", "return", "else",
    "struct", "union", "typedef", "static", "enum", "class", "case",
    "int|", "long|", "double|", "float|", "char|", "unsigned|", "signed|",
    "void|", NULL};

char *CPP_HL_extensions[] = {".cpp", ".h", NULL};
char *CPP_HL_keywords[] = {
    "switch", "if", "while", "for", "break", "continue", "return", "else",
    "struct", "union", "typedef", "static", "enum", "class", "case",
    "int|", "long|", "double|", "float|", "char|", "unsigned|", "signed|",
    "void|", NULL};

struct editorSyntax HLDB[] = {
    {"C",
     C_HL_extensions,
     C_HL_keywords,
     "//", "/*", "*/",
     HL_HIGHLIGHT_STRINGS | HL_HIGHLIGHT_NUMBERS},

    {"C++",
     CPP_HL_extensions,
     CPP_HL_keywords,
     "//", "/*", "*/",
     HL_HIGHLIGHT_STRINGS | HL_HIGHLIGHT_NUMBERS}};

// HLDB stands for highlight database
#define HLDB_ENTRIES (sizeof(HLDB) / sizeof(HLDB[0]))

void editorSetStatusMessage(const char *fmt, ...);
void editorRefreshScreen();
char *editorPrompt(char *prompt, void (*callback)(char *, int));