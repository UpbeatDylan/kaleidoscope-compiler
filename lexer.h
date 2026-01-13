#ifndef KALEIDOSCOPE_LEXER_H
#define KALEIDOSCOPE_LEXER_H

#include <string>

// Token definitions
enum Token
{
    tok_eof = -1,

    // commands
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5,
};

// Filled in if tok_identifier
extern std::string IdentifierStr;

// Filled in if tok_number
extern double NumVal;

// Get the next token from standard input
int gettok();

#endif // KALEIDOSCOPE_LEXER_H
