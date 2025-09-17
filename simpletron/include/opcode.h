#ifndef SIMPLETRON_OPCODE_H
#define SIMPLETRON_OPCODE_H

typedef enum {
    READ       = 10,
    WRITE      = 11,
    LOAD       = 20,
    LOADIM     = 21,
    LOADX      = 22,
    LOADIDX    = 23, 
    STORE      = 25,
    STOREIDX   = 26,
    ADD        = 30,
    ADDX       = 31,
    SUBTRACT   = 32,
    SUBTRACTX  = 33,
    DIVIDE     = 34,
    DIVIDEX    = 35,
    MULTIPLY   = 36,
    MULTIPLYX  = 37,
    INC        = 38,
    DEC        = 39,
    BRANCH     = 40,
    BRANCHNEG  = 41,
    BRANCHZERO = 42,
    SWAP       = 43,
    HALT       = 45
} op_code;

#endif