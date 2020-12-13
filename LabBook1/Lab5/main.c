#include <stdio.h>
#include "shell.h"
#include "board.h"
#include "thread.h"

char stack[THREAD_STACKSIZE_MAIN];

void *_thread_handler(void *arg)
{
    (void) arg;
    kernel_pid_t pid = thread_getpid();
    printf("Hello from thread (pid = %d)\n", pid);
    for(;;);
    return NULL;
}

static const shell_command_t shell_commands[] = {
    { NULL, NULL, NULL }
};

int main(void)
{
    thread_create(stack,
                        sizeof(stack),
                        THREAD_PRIORITY_IDLE,
                        THREAD_CREATE_WOUT_YIELD,
                        _thread_handler,
                        NULL,
                        "_thread_handler");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}