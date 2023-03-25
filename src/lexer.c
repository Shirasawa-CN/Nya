///===========================================================
/// ÊµÏÖlexerÄ£¿é
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