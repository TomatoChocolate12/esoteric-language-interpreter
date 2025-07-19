#ifndef LEXER_HPP
#define LEXER_HPP

#include "tokens.hpp"
#include "interpreter.hpp"


class Lexer {
private:
    string_view source;
    size_t position = 0;
    static const unordered_map<string_view, TokenType> keywords;
    void skipSingleLineComment();
    void skipMultiLineComment();
    void skipWhitespace();
    string_view readWord();
public:
    explicit Lexer(string_view src);
    vector<Token> tokenize();

};

const unordered_map<string_view, TokenType> Lexer::keywords = {
    {"chalo", TokenType::CHALO},
    {"ruko", TokenType::RUKO},
    {"badhao", TokenType::BADHAO},
    {"ghatao", TokenType::GHATAO},
    {"bolo", TokenType::BOLO},
    {"suno", TokenType::SUNO},
    {"ghumo", TokenType::GHUMO},
    {"baitho", TokenType::BAITHO}
};

#endif