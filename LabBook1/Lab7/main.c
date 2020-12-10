#include <stdio.h>
#include "board.h"
#include "thread.h"
#include "periph/gpio.h"
#include "shell.h"

#define LED2_PIN    GPIO_PIN(PORT_A, 5)
#define BP1_PIN     GPIO_PIN(PORT_C, 13)

char stack[THREAD_STACKSIZE_MAIN];

void *_thread_handler(void *arg)
{
    (void) arg;
    for(;;)
    {
        gpio_write(LED2_PIN,gpio_read(BP1_PIN));
    }    
    return NULL;
}


static const shell_command_t shell_commands[] = {
    { NULL, NULL, NULL }
};

int main(void)
{
    thread_create(  stack,
                    sizeof(stack),
                    THREAD_PRIORITY_MAIN + 1,
                    THREAD_CREATE_WOUT_YIELD,
                    _thread_handler,
                    NULL,
                    "_thread_handler");
    gpio_init(LED2_PIN, GPIO_OUT);
    gpio_init(BP1_PIN, GPIO_IN);
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}