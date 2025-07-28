#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "parser.hpp"
#include <span>
#include <vector>
#include <iostream>

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