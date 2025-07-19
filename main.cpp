#include "main.hpp"
#include "tokens.hpp"
#include "parser.hpp"
#include "interpreter.hpp"
#include "lexer.hpp"

using namespace std;

class BrainFuckInterpreter {
public:
    static void run(string_view source) {
        try {
            // Lexing phase
            Lexer lexer(source);
            auto tokens = lexer.tokenize();
            
            // Parsing phase
            auto instructions = Parser::parse(tokens);
            
            // Execution phase
            Interpreter interpreter;
            interpreter.execute(instructions);
            
        } catch (const InterpreterError& e) {
            cerr << "Interpreter Error: " << e.what() << endl;
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
};

int main() {
    string source;
    string line;
    
    while (getline(cin, line)) {
        source += line + '\n';
    }
    
    BrainFuckInterpreter::run(source);
    
    return 0;
}