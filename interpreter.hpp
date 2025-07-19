#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "main.hpp"
#include "parser.hpp"

class Interpreter {
private:
    vector<uint8_t> tape;
    size_t tape_pointer = 0;
    size_t instruction_pointer = 0;

    void ensureTapeSize(size_t required_size);

public:
    Interpreter();
    void execute(span<const Instruction> instructions);
};

class InterpreterError : public std::runtime_error {
public:
    explicit InterpreterError(const string& msg);
};

#endif