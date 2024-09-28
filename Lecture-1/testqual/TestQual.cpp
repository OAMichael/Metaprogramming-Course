#include <iostream>
#include <algorithm>

#include "Lexer.h"

namespace TestQual {

static inline void GetRidOfWestConst(std::vector<Token> &tokens) {
    if (tokens.size() >= 2 && tokens[0] == Token::Const && tokens[1] == Token::Char) {
        tokens[0] = Token::Char;
        tokens[1] = Token::Const;
    }
}

// Check type correctness for tokens "const", "char", "*" and "[]"
// Note: Do not take into account west const since we have replaced it with east const already
static bool CheckTypeCorrectness(const std::vector<Token> &tokens) {
    // Empty type
    if (tokens.size() == 0) {
        return false;
    }
    // Type begins with not "char" (remember that we have replaced west const)
    if (tokens.size() >= 1 && tokens[0] != Token::Char) {
        return false;
    }
    // Multiple "char" tokens
    if (std::count(tokens.cbegin(), tokens.cend(), Token::Char) != 1) {
        return false;
    }
    // If there is an array token in the type, then it must be last token and only array token
    const auto arrCount = std::count(tokens.cbegin(), tokens.cend(), Token::Array);
    if (arrCount != 0 && !(arrCount == 1 && tokens.back() == Token::Array)) {
        return false;
    }

    // Check for duplicate "const" tokens
    // Every "const" applies to what stands to the left with only possible exception of the
    // first one (east/west const) but we have already replaced it with east const
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i] == Token::Const && tokens[i - 1] == Token::Const) {
            return false;
        }
    }

    return true;
}

static void DecomposeQual(const std::vector<Token> &tokens, std::vector<char> &quals) {
    const size_t pointerCount = std::count(tokens.cbegin(), tokens.cend(), Token::Pointer);
    const size_t arrayCount = std::count(tokens.cbegin(), tokens.cend(), Token::Array);
    quals.resize(pointerCount + arrayCount + 1);
    std::fill(quals.begin(), quals.end(), 0);

    auto qualIt = quals.begin();
    for (auto tokIt = tokens.begin(), tokEnd = tokens.end(); tokIt != tokEnd; ++tokIt) {
        switch (*tokIt) {
            case Token::Const: {
                *qualIt = 1;
                break;
            }
            case Token::Char: {
                break;
            }
            case Token::Pointer:
            case Token::Array: {
                ++qualIt;
                break;
            }
            default:;
        }
    }
}

static bool CheckTypesConvertible(const std::vector<char> &aQuals, const std::vector<char> &bQuals) {
    // First check if number of qualifiers match (i.e. number of pointers + arrays)
    if (aQuals.size() != bQuals.size()) {
        return false;
    }

    // Then check if all qualifiers coincide
    auto aIt = aQuals.begin();
    auto bIt = bQuals.begin();
    auto bEnd = bQuals.end();
    while (bIt != bEnd) {
        if (*aIt != *bIt) {
            break;
        }
        ++aIt;
        ++bIt;
    }

    if (bIt == bEnd) {
        return true;
    }

    // If not, Check for const all qualifiers before mismatch
    auto bItPrevEnd = bQuals.begin();
    std::advance(bItPrevEnd, bQuals.size() - 1);
    while (bIt != bItPrevEnd) {
        if (*bIt != 1) {
            return false;
        }
        ++bIt;
    }
    return true;
}


bool testqual(const std::string &a, const std::string &b) {
    Lexer lexer{};
    std::vector<Token> aTokens{};
    std::vector<Token> bTokens{};
    if (!lexer.lex(a, aTokens) || !lexer.lex(b, bTokens)) {
        return false;
    }

    // Get rid of west const to ease processing
    GetRidOfWestConst(aTokens);
    GetRidOfWestConst(bTokens);

    // Check type correctness
    if (!CheckTypeCorrectness(aTokens) || !CheckTypeCorrectness(bTokens)) {
        return false;
    }

    // Fast check
    if (std::count(bTokens.cbegin(), bTokens.cend(), Token::Array) > 0) {
        return false;
    }

    std::vector<char> aQuals{};
    std::vector<char> bQuals{};
    DecomposeQual(aTokens, aQuals);
    DecomposeQual(bTokens, bQuals);

    return CheckTypesConvertible(aQuals, bQuals);
}

}   // namespace TestQual
