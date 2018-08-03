//  Chris Selling
//    cselling 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <strings.h>

#include "stringtable.h"

#define CPP "/usr/bin/cpp"

void cpplines(FILE*, char*, stringtable_ref);

int main(int argc, char** argv){
   stringtable_ref table = new_stringtable();
   for(int i = 1; i < argc; i++){
      char command[strlen(CPP) + 1 + strlen(argv[i]) + 1];
      strcpy(command, CPP);
      strcat(command, " ");
      strcat(command, argv[i]);
      FILE* pipe = popen(command, "r");
      if(pipe == NULL)  fprintf(stderr, "file not found");
      else{
         cpplines(pipe, argv[i], table);
         pclose(pipe);
      }
   }
   dumpdebug(stderr, table);
   return 0;
}

void chomp(char* string, char delim){
   if(strlen(string) == 0 ) return;
   char* check = string + strlen(string) - 1;
   if(*check == delim) *check = NULL;
}

void cpplines(FILE* pipe, char* filename, stringtable_ref table){
   int line = 1;
   char input[1024];
   strcpy(input, filename);
   for(;;){
      char buffer[1024];
      char* fetch = fgets(buffer, 1024, pipe);
      if(fetch == NULL) break;
      chomp(fetch, '\n');
    //  printf("%s:line %d: [%s]\n", filename, line, buffer);
      int scan = sscanf(buffer, "# %d \"%[^\"]\"", &line, filename);
      if(scan == 2){
  //       printf("DIRECTIVE: line %d file \"%s\"\n", line, filename);
         continue;
      }
      char* position = NULL;
      char* bufptr = buffer;
      int stringFlag = 0;
      int operatorFlag = 0;
      char* key = NULL;
      for (int tokenct = 1;; tokenct++){
         char* token = strtok_r(bufptr, " \t\n", &position);
         bufptr = NULL;
         if(token == NULL) break;
         printf("token %d.%d: [%s]\n", line, tokenct, token);
         if(stringFlag){
            if(operatorFlag){
               stringnode_ref temp = intern_stringtable(table, key);
               temp->word = token;
            }
         }
      }
      line++;
   }
}

