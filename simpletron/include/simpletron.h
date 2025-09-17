#ifndef SIMPLETRON_STRUCTURE_H
#define SIMPLETRON_STRUCTURE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/errors.h"

#define MEM_BUFF_SIZE 10000
#define PAGE_TOTAL 100
#define PAGE_COLS 10
#define PAGE_ROWS 10

typedef struct Simpletron {
    int memory[MEM_BUFF_SIZE];
    int accumulator;
    int instr_ctr;
    int index_reg;
    int instr_reg;
    int usr_prog_words;
} Simpletron;

void dump_core(Simpletron* s_tron, int page_low, int page_high);
int get_op_code(Simpletron* s_tron);
int get_operand(Simpletron* s_tron);
int get_upper_operand(Simpletron* s_tron);
int get_lower_operand(Simpletron* s_tron);
SPLTRN_ERR simpletron_execute(Simpletron* s_tron);

#endif