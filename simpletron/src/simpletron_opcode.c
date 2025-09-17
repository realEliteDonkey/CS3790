#include "../include/op_func.h"
#include "stdio.h"

/*
 	Read a word from the terminal into a location whose address is the operand
*/
void read(Simpletron* s_tron) {
    int word;
    int mem_add = get_operand(s_tron);
    printf("Enter 6-digit Word: ");
    scanf("%d", &word);
    s_tron->memory[mem_add] = word;
    printf("\n");
}

/*
    Write a word from the location whose address is the operand to the terminal
*/
void write(Simpletron* s_tron) {
    printf("%d\n", s_tron->memory[get_operand(s_tron)]);
}

/*
    Load a word from the memory location specified by the operand into the accumulator
*/
void load(Simpletron* s_tron) {
    s_tron->accumulator = s_tron->memory[get_operand(s_tron)];
}

/*
    Load the operand into the accumulator
*/
void loadim(Simpletron* s_tron) {
    s_tron->accumulator = get_operand(s_tron);
}

/*
    Load word from the memory location specified by the operand into the index register
*/
void loadx(Simpletron* s_tron) {
    s_tron->index_reg = s_tron->memory[get_operand(s_tron)];
}

/*
    Load word from the memory location specified by index register into accumulator
*/
void loadidx(Simpletron* s_tron) {
    s_tron->accumulator = s_tron->memory[s_tron->index_reg];
}

/*
    Store a word from the acccumulator into the memory location specified by the operand
*/
void store(Simpletron* s_tron) {
    s_tron->memory[get_operand(s_tron)] = s_tron->accumulator;
}

/*
    store a word from the accumulator into a memory location specified by index register
*/
void storeidx(Simpletron* s_tron) {
    s_tron->memory[s_tron->index_reg] = s_tron->accumulator;
}

/*
    Add the word in memory whose address is the operand to the accumulator
    and leave result in accumulator ( ACC += MEM )
*/
void add(Simpletron* s_tron) {
    s_tron->accumulator += s_tron->memory[get_operand(s_tron)];
}

/*
    Add a word in memory whose address is stored in index register to the accumulator
    and leave result in accumulator
*/
void addx(Simpletron* s_tron) {
    s_tron->accumulator += s_tron->memory[s_tron->index_reg];
}

/*
    Subtract a word whose address stored in the operand from the accumulator
    and leave result in accumulator ( ACC -= MEM )
*/
void subtract(Simpletron* s_tron) {
    s_tron->accumulator -= s_tron->memory[get_operand(s_tron)];
}

/*
    Subtract a word whose address is stored in the index register from the accumulator
    and leave result in accumulator 
*/
void subtractx(Simpletron* s_tron) {
    s_tron->accumulator -= s_tron->memory[s_tron->index_reg];
}

/*
    Multiply the accumulator by a word from a specific location in memory
    and leave result in accumulator ( ACC *= MEM )
*/
void multiply(Simpletron* s_tron) {
    s_tron->accumulator *= s_tron->memory[get_operand(s_tron)];
}

/*
    Multiply the accumulator by a word whose address is stored in the index register
    and leave result in accumulator
*/
void multiplyx(Simpletron* s_tron) {
    s_tron->accumulator *= s_tron->memory[s_tron->index_reg];
}

/*
    Divide the accumulator by a word whose address stored in the operand
    and leave result in accumulator and lose the remainder.( ACC /= MEM )   
*/
void divide(Simpletron* s_tron) {
    if (get_operand(s_tron) == 0) {
        printf("ERR: DIVIDE BY ZERO!\n");
        return;
    }
    s_tron->accumulator /= s_tron->memory[get_operand(s_tron)];
}

/*
    Divide the accumulator by a word whose address is stored in the index register
    and leave result in accumulator and lose the remainder.
*/
void dividex(Simpletron* s_tron) {
    if (get_operand(s_tron) == 0) {
        printf("ERR: DIVIDE BY ZERO!\n");
        return;
    }
    s_tron->accumulator /= s_tron->memory[s_tron->index_reg];
}

/*
    increase index register by 1 
*/
void inc(Simpletron* s_tron) {
    s_tron->index_reg++;
}

/*
 	decrease index register by 1 
*/
void dec(Simpletron* s_tron) {
    s_tron->index_reg--;
}

/*
 	Branch to a specific location in memory, location address is in operand
*/
bool branch(Simpletron* s_tron) {
    s_tron->instr_ctr = get_operand(s_tron);
    return true;
}

/*
    Branch to a specific location in memory if accumulator is negative
*/
bool branchneg(Simpletron* s_tron) {
    if (s_tron->accumulator < 0) {
        s_tron->instr_ctr = get_operand(s_tron);
        return true;
    }
    return false;
}

/*
    Branch to a specific location in memory if the accumulator is zero
*/
bool branchzero(Simpletron* s_tron) {
    if (s_tron->accumulator == 0) {
        s_tron->instr_ctr = get_operand(s_tron);
        return true;
    }
    return false;
}

/*
    swap contents of index register and accumulator
*/
void swap(Simpletron* s_tron) {
    int tmp = s_tron->accumulator;
    s_tron->accumulator = s_tron->index_reg;
    s_tron->index_reg = tmp;
}

/*
     	halt program dump register values and a range of pages. 
        The starting page of the range is stored as the top 2 digits 
        of the operand and the last page as the least 
        significant 2 digits( core dump )
*/
void halt(Simpletron* s_tron) {
    int low = get_upper_operand(s_tron);
    int high = get_lower_operand(s_tron);
    dump_core(s_tron, low, high);
}
