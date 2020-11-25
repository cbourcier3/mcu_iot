#include <stdio.h>
#include "shell.h"
int main(void)
{
	char line_buf[SHELL_DEFAULT_BUFSIZE];
	shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
	printf("RIOT Base application\n");
	return 0;	
}

