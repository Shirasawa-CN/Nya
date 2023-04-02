///===========================================================
/// 实现lexer模块
///
///===========================================================
#include "lexer.h"

inline int
check(char* word, int len)
{
  if (len >= SHORTEST_KEYWORD && len <= LONGEST_KEYWORD) {
    for (int i = 0; i < NUMBER_OF_KEYWORD; i++) {
      if (!strcmp(word, Keywords[i]))
        return i;
    }
  }
  return NAME;
}

#define nextChar(word) fnNextChar(file, word);
inline _Bool
fnNextChar(FILE* file, char word)
{
  if (fgetc(file) == word)
    return 1;
  fseek(file, -1, SEEK_CUR);
  return 0;
}

#define newTokenGroup                                                          \
  tokenStruct* tmp =                                                            \
    (tokenStruct*)realloc(G.tokenGroup, sizeof(tokenStruct) * (G.length + 1));  \
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
        char* tmp =                                                            \
          realloc(G.tokenGroup[G.length].word, (length + 1) * sizeof(char));   \
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

extern inline tokenGroup
buildTokenGroup(FILE* file)
{
  tokenGroup G = { (tokenStruct*)calloc(2, sizeof(tokenStruct)), 0, 0 };

  unsigned int line = 0, length = 0;
  char* word = (char*)malloc(sizeof(char));

  char tmp_c;

  while ((tmp_c = fgetc(file)) != EOF) {
    switch (tmp_c) {
      case '=':
      case '!':
      case ';':
      case '&':
      case '|':
      case '+':
      case '-':
      case '*':
        endTokenGroup;
        newTokenGroup;
        G.tokenGroup[G.length].type = tmp_c;
        free(G.tokenGroup[G.length].word);
        break;
      case '/':
      case '{':
      case '}':
      case '(':
      case ')':
      case '[':
      case ']':
      case '#':
      case '@':
      case '^':
      /// ~ 可以释放内存
      case '~':
      default:
        if (word) {
          char* tmp = (char*)realloc(word, sizeof(char) * (length + 1));
          if (tmp) {
            word = tmp;
            word[length++] = tmp_c;
          }
        }
    }
  }

  free(word);
  fclose(file);
  return G;
}

inline void
free_tokenGroup(tokenGroup group)
{
  for (int i = 0; i < group.length; i++) {
    group.tokenGroup[i].word = "CLEAN";
    free(group.tokenGroup[i].word);
  }
  free(group.tokenGroup);
}

inline void
printTokenGroupInTest(tokenGroup group)
{
  for (unsigned int i = 0; i < group.length; i++)
    printf("{ type = %d wordlen = %d line = %d word=%s } \n",
           group.tokenGroup[i].type,
           group.tokenGroup[i].length,
           group.tokenGroup[i].line,
           group.tokenGroup[i].word);
}