#include <stdio.h>
#include "board.h"
#include "thread.h"
#include "periph/gpio.h"
#include "shell.h"
#include "msg.h"
#include "spi.h"

#define LED2_PIN    GPIO_PIN(PORT_A, 5)
#define BP1_PIN     GPIO_PIN(PORT_C, 13)

char stack[THREAD_STACKSIZE_MAIN];
msg_t rcv_queue[2];
static kernel_pid_t rcv_pid;

void _bp_callback(void *arg)
{
    (void) arg;
    msg_t msg;
    msg.content.value = 1;
    msg_try_send(&msg, rcv_pid); 
}

void *_led_toggle_handler(void *arg)
{
    (void) arg;
    for(;;)
    {
        msg_t msg;
        msg_receive(&msg);
        gpio_toggle(LED2_PIN); 
    }
}

static const shell_command_t shell_commands[] = {
    { NULL, NULL, NULL }
};

int main(void)
{
    gpio_init(LED2_PIN, GPIO_OUT);
    gpio_init_int(BP1_PIN, GPIO_IN, GPIO_FALLING, _bp_callback, NULL);
    msg_init_queue(rcv_queue, 2);

    rcv_pid = thread_create(  stack,
                    sizeof(stack),
                    THREAD_PRIORITY_MAIN - 1,
                    THREAD_CREATE_WOUT_YIELD,
                    _led_toggle_handler,
                    NULL,
                    "_led_toggle_handler");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}