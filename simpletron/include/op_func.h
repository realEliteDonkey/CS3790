#ifndef SPL_TRN_OP_CODE_FUNCTIONS_H
#define SPL_TRN_OP_CODE_FUNCTIONS_H

#include "simpletron.h"

void read(Simpletron* s_tron);
void write(Simpletron* s_tron);
void load(Simpletron* s_tron);
void loadim(Simpletron* s_tron);
void loadx(Simpletron* s_tron);
void loadidx(Simpletron* s_tron);
void store(Simpletron* s_tron);
void storeidx(Simpletron* s_tron);
void add(Simpletron* s_tron);
void addx(Simpletron* s_tron);
void subtract(Simpletron* s_tron);
void subtractx(Simpletron* s_tron);
void divide(Simpletron* s_tron);
void dividex(Simpletron* s_tron);
void multiply(Simpletron* s_tron);
void multiplyx(Simpletron* s_tron);
void inc(Simpletron* s_tron);
void dec(Simpletron* s_tron);
bool branch(Simpletron* s_tron);
bool branchneg(Simpletron* s_tron);
bool branchzero(Simpletron* s_tron);
void swap(Simpletron* s_tron);
void halt(Simpletron* s_tron);

#endif