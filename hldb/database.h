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
    "void|", "using", "namespace", "cout", "cin", ">>", "<<", NULL};

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