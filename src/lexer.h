///===========================================================
/// 定义lexer模块
///
///===========================================================

#ifndef NYA_LEXER_H
#define NYA_LEXER_H

#include <cstdio>
#include <cstdlib>
#include <string>

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

  NUMBER,
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

  N_EOF,
  POINTER,
  IDENTIFIER,
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

  "EOF",
};

static std::string IdentifierStr;
static double NumVal;
static fpos_t position;

class lexer
{
private:
  int check(char* word, int len);

public:
  int getToken(FILE* file);
};

#endif // NYA_LEXER_H
