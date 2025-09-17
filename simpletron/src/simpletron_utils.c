#include "../include/simpletron_utils.h"

const char* title_display =
"*** Welcome to Simpletron V2! ***\n"
"***\n"
"Do you have a file that contains your SML program (Y/N) ? ";

const char* manual_enter_instr = 
"*** Please enter your program one instruction( or data word ) at a time        ***\n"
"*** I will type the location number and a question mark (?). You then          ***\n"
"*** type the word for that location. Type the word GO to execute  your program ***\n\n";

const char* auto_entry_instr = 
"Filename: ";


void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}



SPLTRN_ERR auto_instr_entry(const char* file_name, Simpletron* s_tron) {
    // open file structure (fopen)
    char f_path_buff[FILE_PATH_SIZE] = "";
    strcat(f_path_buff, file_name);
    FILE* file = fopen(f_path_buff, "r");
    if (file == NULL) return OPEN_FILE_FAILED;

    // read file contents into instruction buffer
    char line[MAX_LINE_LEN + 100];
    while (fgets(line, MAX_LINE_LEN + 100, file) != NULL) {
        // remove "//" comments"
        char* comment = strstr(line, "//");
        if (comment) *comment = '\0';

        size_t len = strlen(line);
        while (len > 0 && !isdigit((unsigned char)line[len-1])) {
            line[--len] = '\0';
        }

        // skip empty lines. This will occur now that we stripped new-lines and carriage-return
        if (len == 0) continue;

        if (len != 6 && (line[0] != '-')) {
            printf("Must be 6 digits! (%s)\n", line);
        } else {
            // store instruction in memory as integer
            // inc IC
            int data = atoi(line);
            s_tron->memory[s_tron->instr_ctr] = data;
            s_tron->instr_ctr++;
            s_tron->usr_prog_words++;
        }
        memset(line, 0, sizeof(line));
    }

    fclose(file);
    s_tron->instr_ctr = 0;

    return SUCCESS;
}



SPLTRN_ERR manual_instr_entry(Simpletron* s_tron) {
    // Add 100 to length for error checking. If users go above 6,
    // the checks will always allow the input but truncate it.
    // This way if someone enters >6 chars, it will always show 7 as length
    // and fail the digit check
    char line[MAX_LINE_LEN + 100];
    int number;
    size_t line_number = 0;

    printf("Enter instructions (type GO or press Enter to finish):\n");
    clear_stdin();

    while (1) {
        printf("%04ld   ", line_number++); 
        fflush(stdout);

        if (fgets(line, MAX_LINE_LEN + 100, stdin) == NULL) break;

        // remove "//" comments"
        char* comment = strstr(line, "//");
        if (comment) *comment = '\0';

        size_t len = strlen(line);
        while (len > 0 && !isdigit((unsigned char)line[len-1])) {
            line[--len] = '\0';
        }

        if (len == 0 || 
            (strcmp(line, "GO") == 0) || strcmp(line, "go")
        ) break;

        if (sscanf(line, "%d", &number) != 1) {
            printf("Invalid input. Must be an integer.\n");
            clear_stdin();
            line_number--;
            continue;
        }

        if (len != 6) {
            printf("Must be 6 digits! (%s)\n", line);
            line_number--;
            continue;
        }

        s_tron->memory[s_tron->instr_ctr++] = number;
        s_tron->usr_prog_words++;
    }

    s_tron->instr_ctr = 0;
    return SUCCESS;
}