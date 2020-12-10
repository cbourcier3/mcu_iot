#include <stdio.h>
#include "board.h"
#include "thread.h"
#include "periph/gpio.h"
#include "shell.h"

#define LED2_PIN    GPIO_PIN(PORT_A, 5)
#define BP1_PIN     GPIO_PIN(PORT_C, 13)

char stack[THREAD_STACKSIZE_MAIN];

void _bp_callback(void *arg)
{
    (void) arg;
    gpio_toggle(LED2_PIN); 
}

static const shell_command_t shell_commands[] = {
    { NULL, NULL, NULL }
};

int main(void)
{
    gpio_init(LED2_PIN, GPIO_OUT);
    gpio_init_int(BP1_PIN, GPIO_IN, GPIO_FALLING, _bp_callback, NULL);

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}