///===========================================================
/// 定义lexer模块
///
///===========================================================
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

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
  "break",  "contiune", "for",       "return", "use",    "match",

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

void
free_tokenGroup(tokenGroup group);

tokenGroup
buildTokenGroup(FILE* file);

int
check(char* word, int len);

void
printTokenGroupInTest(tokenGroup group);