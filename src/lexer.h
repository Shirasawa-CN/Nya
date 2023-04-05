///===========================================================
/// 定义lexer模块
///
///===========================================================

#ifndef NYA_LEXER_H
#define NYA_LEXER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define LONGEST_KEYWORD 10
#define SHORTEST_KEYWORD 2
#define NUMBER_OF_KEYWORD 34

enum Tokens
{
  TRUE,
  FALSE,
  IF,
  ELSE,
  FN,
  WHILE,
  BREAK,
  CONTIUNE,
  FOR,
  RETURN,
  USE,
  MATCH,

  AND,
  OR,
  XOR,

  L_AND,
  L_OR,

  ADD,
  SUB,
  MUL,
  DIV,

  USIZE,
  ISIZE,
  FSIZE,
  CHAR,
  NAME,
  FN_NAME,

  STRUCT,
  ENUM,
  UNION,

  STATIC,
  CONST,
  NAMESPACE,
  FREE,
  DROP,
};

static const char* const Keywords[] = {
  "true",   "false",    "if",        "else",   "fn",     "while",
  "break",  "continue", "for",       "return", "use",    "match",

  "&",      "|",        "^",

  "&&",     "||",

  "+",      "-",        "*",         "/",

  "usize",  "isize",    "fsize",     "char",   "string",

  "struct", "enum",     "union",

  "static", "const",    "namespace", "free",   "drop",
};

typedef struct
{
  char* word;
  int type;
  unsigned int length;
  unsigned int line;
} tokenStruct;

typedef struct
{
  tokenStruct* tokenGroup;
  unsigned int length;
  int panic;
} tokenGroup;

#define newTokenGroup                                                          \
  tokenStruct* tmp =                                                           \
    (tokenStruct*)realloc(G.tokenGroup, sizeof(tokenStruct) * (G.length + 1)); \
  G.tokenGroup = tmp;                                                          \
                                                                               \
  G.tokenGroup[G.length].line = line;                                          \
  G.tokenGroup[G.length].length = 0;                                           \
  G.tokenGroup[G.length].type = 0;                                             \
  G.tokenGroup[G.length].word = NULL;

#define endTokenGroup                                                          \
  if (length) {                                                                \
    newTokenGroup;                                                             \
    int i;                                                                     \
    if ((i = check(word, length)) == NAME) {                                   \
      if (G.tokenGroup[G.length].word) {                                       \
        char* tmp = (char*)realloc(G.tokenGroup[G.length].word,                \
                                   (length + 1) * sizeof(char));               \
        if (tmp)                                                               \
          G.tokenGroup[G.length].word = tmp;                                   \
      }                                                                        \
      memcpy(G.tokenGroup[G.length].word, word, length);                       \
      G.tokenGroup[G.length].word[length++] = '\0';                            \
      G.tokenGroup[G.length].length = length;                                  \
      G.tokenGroup[G.length++].type = NAME;                                    \
    } else {                                                                   \
      G.tokenGroup[G.length].type = i;                                         \
      free(G.tokenGroup[G.length++].word);                                     \
    }                                                                          \
    length = 0;                                                                \
    word = (char*)calloc(2, sizeof(char));                                     \
  }

class lexer
{

  void free_tokenGroup(tokenGroup group);

  int check(char* word, int len);

public:
  tokenGroup buildTokenGroup(FILE* file);

  void printTokenGroupInTest(tokenGroup group);
};

#endif // NYA_LEXER_H
