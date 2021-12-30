#include <stdio.h>
#include <stdlib.h>

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
    puts("Lisp Version 0.0.0.0.1");
    puts("Press Ctrl+C to exit\n");

    while (TRUE) {
        char* input = readline(PROMPT);
        add_history(input);

        printf("No you're a %s", input);
        free(input); // liberamos `input` porque es un puntero (char*)
    }

    return 0;
}