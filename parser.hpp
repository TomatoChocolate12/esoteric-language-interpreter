#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP


enum class InstructionType {
    MOVE_RIGHT,
    MOVE_LEFT,
    INCREMENT,
    DECREMENT,
    OUTPUT,
    INPUT,
    JUMP_FORWARD,
    JUMP_BACKWARD
};

struct Instruction {
    InstructionType type;
    size_t jump_target = 0; // For jump instructions
};

#endif