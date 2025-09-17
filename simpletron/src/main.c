#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/simpletron_utils.h"
#include "../include/simpletron.h"

int main() {

   Simpletron* simpletron = malloc(sizeof(Simpletron));
   memset(simpletron, 0, sizeof(Simpletron));

   title:
   printf("%s", title_display);
   char bool_input[1];
   scanf("%1s", bool_input);

   bool_input[0] = toupper(bool_input[0]);
   /*
      Receives user input for automatic file input or manual instruction input
   */
   if (bool_input[0] == 'Y') {
      printf("\n\n%s", auto_entry_instr);
      // get file name
      // check file exists
      char file_name[64];
      scanf("%64s", file_name);
      
      // load file instructions into memory
      SPLTRN_ERR result = auto_instr_entry(file_name, simpletron);
      if (result == OPEN_FILE_FAILED) {
         printf("Failed to open SML file.\n");
         exit(1);
      }
   }
   else if (bool_input[0] == 'N') {
      printf("\n\n%s", manual_enter_instr);
      
      SPLTRN_ERR result = manual_instr_entry(simpletron);
      if (result != SUCCESS) {
         printf("Unsuccessful instruction entry.\n");
         exit(1);
      }
   } else {
      printf("Invalid input.\n\n");
      goto title;
   }

   SPLTRN_ERR result = simpletron_execute(simpletron);
   
   if (result == EXECUTE_FAIL) {
      printf("EXECUTION FAILED!\nEXITING PROGRAM EXECUTION...\n");
      return EXECUTE_FAIL;
   }

   free(simpletron);
   return SUCCESS;
}
