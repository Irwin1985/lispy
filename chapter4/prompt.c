#include <stdio.h>
#define MAX_INPUT 2048
#define TRUE 1 // Cualquier tipo distinto de cero es true.
#define PROMPT "lisp> "

static char input[MAX_INPUT];

int main() {
    puts("Lisp Version 0.0.0.0.1");
    puts("Press Ctrl+C to exit\n");

    while (TRUE) {
        fputs(PROMPT, stdout);
        fgets(input, MAX_INPUT, stdin);
        printf("No you're a %s", input);
    }

    return 0;
}