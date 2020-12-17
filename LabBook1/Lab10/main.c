#include <stdio.h>
#include <string.h>
#include "board.h"
#include "thread.h"
#include "shell.h"
#include "xtimer.h"
#include "/home/etudiant/riot/RIOT/drivers/tsl2561/include/tsl2561_params.h"

char stack[THREAD_STACKSIZE_MAIN];
static tsl2561_t sensor;

void *_blink_handler(void *arg)
{
    (void) arg;
    xtimer_ticks32_t timer;
    xtimer_init();
    timer = xtimer_now();
    printf("Début du thread\n");
    for(;;)
    {
        printf("%d\n",tsl2561_read_illuminance(&sensor));
        xtimer_periodic_wakeup(&timer , 3000000);
    }    
    return NULL;
}

int main(void)
{
    int err = -666;
    err = tsl2561_init(&sensor, &tsl2561_params[0]);
    if (err != 0) return err;
    thread_create(  stack,
                    sizeof(stack),
                    THREAD_PRIORITY_MAIN + 1,
                    0,
                    _blink_handler,
                    NULL,
                    "_blink_handler");
    return 0;
}


/* 
TSL2561 datasheet : 
    I2C Address :   0101001 if GND  => 0x29
                    0111001 if Float=> 0x39
                    1001001 if Vcc  => 0x49
Grove light sensor breakout
    I2C Address :   0x29
Four parameters needed for tsl2561 device driver :
    Data Fields
        i2c_t   i2c_dev
            I2C device which is used.
        uint8_t     addr
            address on I2C bus
        uint8_t     gain
            gain
        uint8_t     integration
            integration time
CFlags configuration : 
    List of compile-time configurations.
#define     TSL2561_PARAM_I2C_DEV   I2C_DEV(0)
#define     TSL2561_PARAM_ADDR   TSL2561_ADDR_FLOAT
#define     TSL2561_PARAM_GAIN   TSL2561_GAIN_1X
#define     TSL2561_PARAM_INTEGRATION   TSL2561_INTEGRATIONTIME_402MS
Module to add for the device driver : 
    tsl2561
Include for the driver :
    #include "tsl2561.h"
    #include "periph/i2c"
    #include "saul.h"

    This group contains all compile-time configurations macros 
    that are intended to be modified by the user.

    These configuration macros are defined within modules like this:

    #ifndef SOME_CONFIGURATION_PARAM
    #define SOME_CONFIGURATION_PARAM DEFAULT_VALUE
    #endif
    Because of that, configurations can be altered e.g via 
    CFLAGS (e.g CFLAGS += -DSOME_CONFIGURATION_PARAM=SOME_VALUE)



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