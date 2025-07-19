#include "interpreter.hpp"

using namespace std;

class Interpreter {
private:
    vector<uint8_t> tape;
    size_t tape_pointer = 0;
    size_t instruction_pointer = 0;
    
    void ensureTapeSize(size_t required_size) {
        if (required_size >= tape.size()) {
            tape.resize(required_size + 1000, 0);
        }
    }
    
public:
    Interpreter() : tape(1000, 0) {}
    
    void execute(span<const Instruction> instructions) {
        instruction_pointer = 0;
        
        while (instruction_pointer < instructions.size()) {
            const auto& instr = instructions[instruction_pointer];
            
            switch (instr.type) {
                case InstructionType::MOVE_RIGHT:
                    ++tape_pointer;
                    ensureTapeSize(tape_pointer);
                    break;
                    
                case InstructionType::MOVE_LEFT:
                    if (tape_pointer == 0) {
                        throw InterpreterError("Tape pointer moved below zero");
                    }
                    --tape_pointer;
                    break;
                    
                case InstructionType::INCREMENT:
                    ensureTapeSize(tape_pointer);
                    ++tape[tape_pointer];
                    break;
                    
                case InstructionType::DECREMENT:
                    ensureTapeSize(tape_pointer);
                    --tape[tape_pointer];
                    break;
                    
                case InstructionType::OUTPUT:
                    ensureTapeSize(tape_pointer);
                    cout << static_cast<char>(tape[tape_pointer]);
                    cout.flush();
                    break;
                    
                case InstructionType::INPUT:
                    ensureTapeSize(tape_pointer);
                    {
                        int ch = cin.get();
                        tape[tape_pointer] = (ch == EOF) ? 0 : static_cast<uint8_t>(ch);
                    }
                    break;
                    
                case InstructionType::JUMP_FORWARD:
                    ensureTapeSize(tape_pointer);
                    if (tape[tape_pointer] == 0) {
                        instruction_pointer = instr.jump_target;
                    }
                    break;
                    
                case InstructionType::JUMP_BACKWARD:
                    ensureTapeSize(tape_pointer);
                    if (tape[tape_pointer] != 0) {
                        instruction_pointer = instr.jump_target;
                    }
                    break;
            }
            
            ++instruction_pointer;
        }
    }
};

class InterpreterError : public std::runtime_error {
public:
    explicit InterpreterError(const string& msg) : std::runtime_error(msg) {}
};