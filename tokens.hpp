#ifndef TOKENS_HPP
#define TOKENS_HPP


enum class TokenType {
    CHALO,     // move right
    RUKO,      // move left
    BADHAO,    // increment
    GHATAO,    // decrement
    BOLO,      // output
    SUNO,      // input
    GHUMO,     // loop start
    BAITHO,    // loop end
    END
};

struct Token {
    TokenType type;
    size_t position;
};

#endif
