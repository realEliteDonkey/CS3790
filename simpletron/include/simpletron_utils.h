#ifndef SIMPLETRON_UTILS_H
#define SIMPLETRON_UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errors.h"
#include "simpletron.h"
#include "ctype.h"


#define FILE_PATH_SIZE 64

// length is 7 to allow for null terminator
#define MAX_LINE_LEN 7

extern const char* title_display;
extern const char* manual_enter_instr;
extern const char* auto_entry_instr;

void clear_stdin();
SPLTRN_ERR auto_instr_entry(const char* file_name, Simpletron* s_tron);
SPLTRN_ERR manual_instr_entry(Simpletron* s_tron);


#endif