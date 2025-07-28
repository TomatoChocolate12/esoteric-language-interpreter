#include "tokens.hpp"
#include "parser.hpp"
#include "interpreter.hpp"

#include <vector>
#include <stack>
#include <span>

using namespace std;

class Parser {
public:
    static vector<Instruction> parse(span<const Token> tokens) {
        vector<Instruction> instructions;
        stack<size_t> loop_stack;
        
        for (const auto& token : tokens) {
            if (token.type == TokenType::END) break;
            
            Instruction instr;
            
            switch (token.type) {
                case TokenType::CHALO:
                    instr.type = InstructionType::MOVE_RIGHT;
                    break;
                case TokenType::RUKO:
                    instr.type = InstructionType::MOVE_LEFT;
                    break;
                case TokenType::BADHAO:
                    instr.type = InstructionType::INCREMENT;
                    break;
                case TokenType::GHATAO:
                    instr.type = InstructionType::DECREMENT;
                    break;
                case TokenType::BOLO:
                    instr.type = InstructionType::OUTPUT;
                    break;
                case TokenType::SUNO:
                    instr.type = InstructionType::INPUT;
                    break;
                case TokenType::GHUMO:
                    instr.type = InstructionType::JUMP_FORWARD;
                    loop_stack.push(instructions.size());
                    break;
                case TokenType::BAITHO:
                    if (loop_stack.empty()) {
                        throw InterpreterError("Mismatched baitho at position " + to_string(token.position));
                    }
                    instr.type = InstructionType::JUMP_BACKWARD;
                    {
                        size_t loop_start = loop_stack.top();
                        loop_stack.pop();
                        instr.jump_target = loop_start;
                        instructions[loop_start].jump_target = instructions.size();
                    }
                    break;
                default:
                    continue;
            }
            
            instructions.push_back(instr);
        }
        
        if (!loop_stack.empty()) {
            throw InterpreterError("Mismatched ghumo - missing baitho");
        }
        
        return instructions;
    }
};