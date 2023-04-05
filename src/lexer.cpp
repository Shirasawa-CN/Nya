///===========================================================
/// 实现lexer模块
///
///===========================================================

#include "lexer.h"

void
lexer::free_tokenGroup(tokenGroup group)
{
  for (int i = 0; i < group.length; i++) {
    *group.tokenGroup[i].word = 'C';
    free(group.tokenGroup[i].word);
  }
  free(group.tokenGroup);
}

int
lexer::check(char* word, int len)
{
  return 0;
}

void
lexer::printTokenGroupInTest(tokenGroup group)
{
  for (unsigned int i = 0; i < group.length; i++) {
    printf("{ type = %d word length = %d line = %d word=%s } \n",
           group.tokenGroup[i].type,
           group.tokenGroup[i].length,
           group.tokenGroup[i].line,
           group.tokenGroup[i].word);
  }
}

tokenGroup
lexer::buildTokenGroup(FILE* file)
{
  tokenGroup G = { (tokenStruct*)malloc(2 * sizeof(tokenStruct)), 0, 0 };

  unsigned int line = 0, length = 0;
  char* word = (char*)malloc(sizeof(char));

  char tmp_c;

  while ((tmp_c = fgetc(file)) != EOF) {
    endTokenGroup;
    newTokenGroup;
    switch (tmp_c) {
      case '=':
      case '!':
      case ';':
      case '&':
      case '|':
      case '+':
      case '-':
      case '*':
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