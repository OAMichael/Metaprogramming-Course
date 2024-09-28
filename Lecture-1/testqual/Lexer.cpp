#include <iostream>

#include "Lexer.h"

namespace TestQual {

bool Lexer::lex(const std::string &input, std::vector<Token> &outTokens) {
    currentChar_ = input.data();
    programEnd_ = input.data() + input.size();

    while (currentChar_ != programEnd_) {
        if (std::isspace(*currentChar_)) {
            ++currentChar_;
            continue;
        }

        switch (*currentChar_) {
            case '*': {
                outTokens.push_back(Token::Pointer);
                ++currentChar_;
                continue;
            }
            case '[': {
                ++currentChar_;
                if (currentChar_ == programEnd_) {
                    std::cerr << "Unexpected end of symbols" << std::endl;
                    return false;
                }
                if (*currentChar_ != ']') {
                    std::cerr << "Invalid token [" << *currentChar_ << std::endl;
                    return false;
                }
                outTokens.push_back(Token::Array);
                ++currentChar_;
                continue;
            }
            default: {
                if (isalpha(*currentChar_)) {
                    std::string currentWord = "";

                    const char *tmp = currentChar_;
                    while ((tmp != programEnd_) && isalpha(*tmp)) {
                        currentWord += *tmp;
                        ++tmp;
                    }

                    if (currentWord == "const") {
                        outTokens.push_back(Token::Const);
                        currentChar_ = tmp;
                        continue;
                    }
                    else if (currentWord == "char") {
                        outTokens.push_back(Token::Char);
                        currentChar_ = tmp;
                        continue;
                    }

                    std::cerr << "Invalid token: " << currentWord << std::endl;
                    return false;
                }

                std::cerr << "Invalid symbol: " << *currentChar_ << std::endl;
                return false;
            }
        }
    }
    return true;
}

}   // namespace TestQual
