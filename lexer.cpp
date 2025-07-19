#include "lexer.hpp"
#include "tokens.hpp"

using namespace std;


class Lexer {
private:
    string_view source;
    size_t position = 0;
    
    static const unordered_map<string_view, TokenType> keywords;
    
    void skipSingleLineComment() {
        while (position < source.size() && source[position] != '\n') {
            ++position;
        }
    }
    
    void skipMultiLineComment() {
        while (position < source.size()) {
            if (position + 4 < source.size() && 
                source.substr(position, 5) == "baane") {
                position += 5;
                return;
            }
            ++position;
        }
        throw InterpreterError("Unterminated multi-line comment");
    }
    
    void skipWhitespace() {
        while (position < source.size() && isspace(source[position])) {
            ++position;
        }
    }
    
    string_view readWord() {
        size_t start = position;
        while (position < source.size() && 
               (isalnum(source[position]) || source[position] == '_')) {
            ++position;
        }
        return source.substr(start, position - start);
    }
    
public:
    explicit Lexer(string_view src) : source(src) {}
    
    vector<Token> tokenize() {
        vector<Token> tokens;
        
        while (position < source.size()) {
            skipWhitespace();
            if (position >= source.size()) break;
            
            size_t token_pos = position;
            string_view word = readWord();
            
            if (word.empty()) {
                ++position; // Skip unknown character
                continue;
            }
            
            // Handle comments
            if (word == "taana") {
                skipSingleLineComment();
                continue;
            }
            
            if (word == "taane") {
                skipMultiLineComment();
                continue;
            }
            
            // Handle keywords
            if (auto it = keywords.find(word); it != keywords.end()) {
                tokens.push_back({it->second, token_pos});
            }
        }
        
        tokens.push_back({TokenType::END, position});
        return tokens;
    }
};