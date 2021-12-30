#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

#define MAX_INPUT 2048
#define TRUE 1 // Cualquier tipo distinto de cero es true.
#define PROMPT "lisp> "

#ifdef _WIN32
    #include <string.h>
    static char buffer[MAX_INPUT];
    // Fake readline function
    char* readline(char* prompt) {
        fputs(prompt, stdout); // escribimos en la consola el contenido de `prompt`
        fgets(buffer, MAX_INPUT, stdin); // obtenemos el input del usuario
        char* cpy = malloc(strlen(buffer)+1); // asignamos memoria para `cpy`
        strcpy(cpy, buffer); // copia en `cpy` lo que haya en `buffer`
        cpy[strlen(cpy)+1] = '\0'; // indicamos el fin del string con '\0'
        return cpy;
    }

    // Fake add_history function
    void add_history(char* unused) {} // no hace nada, solo para simular
#else
    #include <editline/readline.h>
    #include <editline/history.h>
#endif    

int main() {
    // ------------------------------------------------------------- //
    // Creamos algunos tipos `mpc_parser_t` (reglas de producción)
    // ------------------------------------------------------------- //
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Lispy = mpc_new("lispy");
    // ------------------------------------------------------------- //
    // Ahora los definimos con las siguientes expresiones regulares
    // ------------------------------------------------------------- //
    mpca_lang(MPCA_LANG_DEFAULT, 
        "                                                             \
        number      : /-?[0-9]+/ ;                                  \
        operator    : '+' | '-' | '*' | '/' ;                       \
        expr        : <number> | '(' <operator> <expr>+ ')' ;        \
        lispy       : /^/ <operator> <expr>+ /$/ ;                  \
        ",
    Number, Operator, Expr, Lispy);

    // ------------------------------------------------------------- //
    puts("Lisp Version 0.0.0.0.1");
    puts("Press Ctrl+C to exit\n");
    while (TRUE) {
        char* input = readline(PROMPT);
        add_history(input);

        // Intentamos Parsear la entrada del usuario.
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            // En caso de Ok imprimimos el AST
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else {
            // en caso error imprimimos el error
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }

    // Undefine and Delete our Parsers
    mpc_cleanup(4, Number, Operator, Expr, Lispy);
    
    return 0;
}