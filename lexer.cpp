#include "lexer.h"

#include <cctype>  // isspace, isalpha, isalnum, isdigit
#include <cstdio>  // getchar
#include <cstdlib> // strtod

// ===== 全局状态（真正的定义，只能在 cpp 里） =====

// Filled in if tok_identifier
std::string IdentifierStr;

// Filled in if tok_number
double NumVal;

// ===== lexer 实现 =====

int gettok()
{
    static int LastChar = ' ';

    // Skip any whitespace.
    while (isspace(LastChar))
        LastChar = getchar();

    // identifier: [a-zA-Z][a-zA-Z0-9]*
    if (isalpha(LastChar))
    {
        IdentifierStr = LastChar;
        while (isalnum(LastChar = getchar()))
            IdentifierStr += LastChar;

        if (IdentifierStr == "def")
            return tok_def;
        if (IdentifierStr == "extern")
            return tok_extern;

        return tok_identifier;
    }

    // Number: [0-9.]+
    if (isdigit(LastChar) || LastChar == '.')
    {
        std::string NumStr;
        do
        {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), nullptr);
        return tok_number;
    }

    // Comment until end of line.
    if (LastChar == '#')
    {
        do
        {
            LastChar = getchar();
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return gettok();
    }

    // Check for end of file.
    if (LastChar == EOF)
        return tok_eof;

    // Otherwise, return the character as its ASCII value.
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}
