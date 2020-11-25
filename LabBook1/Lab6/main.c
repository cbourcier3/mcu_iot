#include <stdio.h>
#include "shell.h"
#include "board.h"
#include "thread.h"
#include "xtimer.h"

char stack[THREAD_STACKSIZE_MAIN];

void *_thread_handler(void *arg)
{
    (void) arg;
    kernel_pid_t pid = thread_getpid();
    for(;;)
    {
        printf("Hello from thread (pid = %d)\n", pid);
        xtimer_usleep(500000);
    }    
    return NULL;
}

void *_blink_handler(void *arg)
{
    (void) arg;
    for(;;)
    {
        LED0_ON;
        xtimer_usleep(250000);
        LED0_OFF;
        xtimer_usleep(250000);
    }    
    return NULL;
}

static const shell_command_t shell_commands[] = {
    { NULL, NULL, NULL }
};

int main(void)
{
    thread_create(      stack,
                    sizeof(stack),
                    THREAD_PRIORITY_MAIN + 1,
                    THREAD_CREATE_WOUT_YIELD,
                    _thread_handler,
                    NULL,
                    "_thread_handler");
    gpio_init(LED0_PIN, GPIO_OUT);
    thread_create(      stack,
                    sizeof(stack),
                    THREAD_PRIORITY_MAIN + 1,
                    THREAD_CREATE_WOUT_YIELD,
                    _blink_handler,
                    NULL,
                    "_blink_handler");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}