#include <stdio.h>
#include "board.h"
#include "thread.h"
#include "shell.h"
#include "lib_lcd_backlight.h"

char stack[THREAD_STACKSIZE_MAIN];
unsigned char rngColor[3] = {0};

void *_blink_handler(void *arg)
{
    (void) arg;
    xtimer_ticks32_t timer;
    xtimer_init();
    timer = xtimer_now();
    for(;;)
    {
        hwrng_read(rngColor, 3);
        lcd_setRGB(I2C_PORT,rngColor[0],rngColor[1],rngColor[2]);
        lcd_puts(I2C_PORT, rngColor);
        xtimer_periodic_wakeup(&timer , 500000);
    }    
    return NULL;
}

static const shell_command_t shell_commands[] = {
    { NULL, NULL, NULL }
};

int main(void)
{
    lcd_init(I2C_PORT);
    hwrng_init();
    lcd_displayOn(I2C_PORT);
    lcd_setRGB(I2C_PORT,255,0,0);
    thread_create(  stack,
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

/**
    // initialize the bus (this is normally done during boot time)
    i2c_init(dev);
    ...
    // before accessing the bus, we need to acquire it
    i2c_acquire(dev);
    // next we write the register address, but create no STOP condition when done
    i2c_write_byte(dev, device_addr, reg_addr, (I2C_NOSTOP | I2C_ADDR10));
    // and now we read the register value
    i2c_read_byte(dev, device_addr, &reg_value, I2C_ADDR10);
    // finally we have to release the bus
    i2c_release(dev);
*/