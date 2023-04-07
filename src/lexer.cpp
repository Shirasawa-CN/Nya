///===========================================================
/// 实现lexer模块
///
///===========================================================

#include "lexer.h"

int
lexer::check(char* word, int len)
{
  return 0;
}

int
lexer::getToken(FILE* file)
{
  fsetpos(file, &position);
  static int LastChar = ' ';

  // Skip any whitespace.
  while (isspace(LastChar))
    LastChar = fgetc(file);

  if (isalpha(LastChar)) {
    IdentifierStr = LastChar;
    while (isalnum((LastChar = fgetc(file))))
      IdentifierStr += LastChar;
    if (IdentifierStr == Keywords[0]) {
      fgetpos(file, &position);
      return Tokens::TRUE;
    }

    if (IdentifierStr == Keywords[1]) {
      fgetpos(file, &position);
      return Tokens::FALSE;
    }

    if (IdentifierStr == Keywords[2]) {
      fgetpos(file, &position);
      return Tokens::IF;
    }

    if (IdentifierStr == Keywords[3]) {
      fgetpos(file, &position);
      return Tokens::FALSE;
    }

    if (IdentifierStr == Keywords[4]) {
      fgetpos(file, &position);
      return Tokens::FN;
    }

    if (IdentifierStr == Keywords[5]) {
      fgetpos(file, &position);
      return Tokens::WHILE;
    }

    if (IdentifierStr == Keywords[6]) {
      fgetpos(file, &position);
      return Tokens::BREAK;
    }

    fgetpos(file, &position);
    return Tokens::IDENTIFIER;
  }
  if (isdigit(LastChar) || LastChar == '.') {
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = fgetc(file);
    } while (isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), nullptr);
    fgetpos(file, &position);
    return Tokens::NUMBER;
  }
  if (LastChar == '#') {
    // Comment until end of line.
    do
      LastChar = fgetc(file);
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF) {
      fgetpos(file, &position);
      return getToken(file);
    }
  }
  if (LastChar == EOF) {
    fgetpos(file, &position);
    return Tokens::N_EOF;
  }

  int ThisChar = LastChar;
  LastChar = fgetc(file);
  fgetpos(file, &position);
  return ThisChar;
}