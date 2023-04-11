#include <stdio.h>
#include "helpers/vector.h"
#include "compiler.h"
int main(){
    int res = compile_file("./test.c","./test",0);
    if(res== COMPILER_FILE_COMPILED_OK){
        printf("Everything compiled fine.\n");
    } else if(res == COMPILER_FAILED_WITH_ERRORS){
        printf("Compile Failed!\n");
    } else{
        printf("Unknown Response\n");
    }
    return 0;
}