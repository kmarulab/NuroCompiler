#include "compiler.h"
#include <stdarg.h>
#include <stdlib.h>

struct lex_process_functions compiler_lex_functions = {
        .next_char=compile_process_next_char,
        .peek_char=compile_process_peek_process,
        .push_char=compile_process_push_process
};

void compiler_error(struct compile_process* compiler,const char* msg, ...){
    va_list args;
    va_start(args,msg);
    vfprintf(stderr,msg,args);
    va_end(args);

    fprintf(stderr,"on line %i, col %i in file %s\n", compiler->pos.line,compiler->pos.col, compiler->pos.filename);
    exit(-1);
}


void compiler_warning(struct compile_process* compiler,const char* msg, ...){
    va_list args;
    va_start(args,msg);
    vfprintf(stderr,msg,args);
    va_end(args);
    fprintf(stderr,"on line %i, col %i in file %s\n", compiler->pos.line,compiler->pos.col, compiler->pos.filename);
}

int compile_file(const char* filename, const char* out_filename, int flags){
    struct compile_process *process = compile_process_create(filename,out_filename,flags);
            if(!process){
                return COMPILER_FAILED_WITH_ERRORS;
            }
            //perform lexical analysis
            struct lex_process* lex_process = lex_process_create(process,&compiler_lex_functions,NULL);
            if(!lex_process){
                return COMPILER_FAILED_WITH_ERRORS;
            }
            if(lex(lex_process)!= LEXICAL_ANALYSIS_ALL_OK){
                return COMPILER_FAILED_WITH_ERRORS;
            }
            //perform parsing

            //perform code generation and generation
    return COMPILER_FILE_COMPILED_OK;
}

/*
lexical analysis
process of turning strings into tokens by lexer
a token has a type and a value
Benefits of Lexical Analysis
Easily Identify source code keywords, symbols, operators etc
less work for parser(WIll only need to deal with tokens)
Token info's in right format
Unnecessary information such as spaces may be discarded

Token Types:
Type Identifier - words with letters under scrolls
Type Keyword - data types, control procedure commands
Type Operator - operations eg. +,-,*,/
Type Symbol - quotes, semicolons colons
Type Number - Numerical Number
Type String - Data between double quotes
Type Comment - comment
Type Newline - new line
*/