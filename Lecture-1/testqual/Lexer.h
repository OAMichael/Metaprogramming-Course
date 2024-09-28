#ifndef LEXEL_H
#define LEXEL_H

#include <string>
#include <vector>

namespace TestQual {

enum Token {
    Const,
    Char,
    Pointer,
    Array,
    Unknown,
};

static const char *tokenNames[] = {
    "Const",
    "Char",
    "Pointer",
    "Array",
    "Unknown",
};


class Lexer {
public:
    bool lex(const std::string &input, std::vector<Token> &outTokens);

private:
    const char *programEnd_ = nullptr;
    const char *currentChar_ = nullptr;
};

}   // namespace TestQual

#endif  // LEXEL_H
