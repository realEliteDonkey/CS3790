#include "../include/simpletron.h"
#include "../include/opcode.h"
#include "../include/op_func.h"

void dump_core(Simpletron* s_tron, int page_low, int page_high) {
    printf("REGISTERS: \n\n");

    printf("%-21s%06d\n", "Accumulator", s_tron->accumulator);
    printf("%-21s%06d\n", "InstructionCounter", s_tron->instr_ctr);
    printf("%-21s%06d\n", "IndexRegister", s_tron->index_reg);
    printf("%-21s%06d\n", "UsrProgWords", s_tron->usr_prog_words);

    // separate instr_reg into op_code and operand
    // size inc by 1 to account for null terminator
    char op_code[3];
    char operand[5];
    char instr_reg[7];

    // convert integer to string
    sprintf(instr_reg, "%06d", s_tron->instr_reg);

    op_code[0] = instr_reg[0];
    op_code[1] = instr_reg[1];
    op_code[2] = '\0';

    operand[0] = instr_reg[2];
    operand[1] = instr_reg[3];
    operand[2] = instr_reg[4];
    operand[3] = instr_reg[5];
    operand[4] = '\0';

    printf("%-21s%02d\n", "OpCode", atoi(op_code));
    printf("%-21s%04d\n\n", "Operand", atoi(operand));

    printf("MEMORY\n\n");

    // print page tables
    int page_start_address = page_low * 100;
    
    for (int page = page_low; page <= page_high; page++) {
        printf("PAGE #%d\n", page);
        printf("%9d%7d%7d%7d%7d%7d%7d%7d%7d%7d\n", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        for (int row = 0; row < 100; row += 10) {
            printf("%02d ", row);
            for (int col = 0; col < 10; col++) {
                printf("%06d ", s_tron->memory[page_start_address]);
                page_start_address++;
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("----------------------------------------\n\n");
}

int get_op_code(Simpletron* s_tron) {
    return s_tron->instr_reg / 10000;
}

int get_operand(Simpletron* s_tron) {
    return s_tron->instr_reg % 10000;
}

int get_upper_operand(Simpletron* s_tron) {
    return get_operand(s_tron) / 100;
}

int get_lower_operand(Simpletron* s_tron) {
    return get_operand(s_tron) % 100;
}

SPLTRN_ERR simpletron_execute(Simpletron* s_tron) {
    s_tron->instr_ctr = 0;
    while (1) {
        s_tron->instr_reg = s_tron->memory[s_tron->instr_ctr];
        bool jump = false;
        switch (get_op_code(s_tron)) {
            case READ:
                read(s_tron);
                break;
            case WRITE:
                write(s_tron);
                break;
            case LOAD:
                load(s_tron);
                break;
            case LOADIM:
                loadim(s_tron);
                break;
            case LOADX:
                loadx(s_tron);
                break;
            case LOADIDX:
                loadidx(s_tron);
                break;
            case STORE:
                store(s_tron);
                break;
            case STOREIDX:
                storeidx(s_tron);
                break;
            case ADD:
                add(s_tron);
                break;
            case ADDX:
                addx(s_tron);
                break;
            case SUBTRACT:
                subtract(s_tron);
                break;
            case SUBTRACTX:
                subtractx(s_tron);
                break;
            case MULTIPLY:
                multiply(s_tron);
                break;
            case MULTIPLYX:
                multiplyx(s_tron);
                break;
            case DIVIDE:
                divide(s_tron);
                break;
            case DIVIDEX:
                dividex(s_tron);
                break;
            case INC:
                inc(s_tron);
                break;
            case DEC:
                dec(s_tron);
                break;
            case BRANCH:
                jump = branch(s_tron);
                break;
            case BRANCHNEG:
                jump = branchneg(s_tron);
                break;
            case BRANCHZERO:
                jump = branchzero(s_tron);
                break;
            case SWAP:
                swap(s_tron);
                break;
            case HALT:
                halt(s_tron);
                return SUCCESS;
        }
        if (!jump) s_tron->instr_ctr++;
    }
    return EXECUTE_FAIL;
}
