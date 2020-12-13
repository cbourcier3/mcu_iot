#include <stdio.h>
#include "board.h"
#include "thread.h"
#include "shell.h"
#include "lib_max31855.h"
int temp = 0;    
unsigned char tempChar[4] = {0};

int _temp_handler(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    max31855_init(SPI_PORT, SPI_CS_PIN);
    max31855_readtemp(SPI_PORT, SPI_CS_PIN, tempChar);
    float tempFloat = max31855_decodetemp(tempChar);
    printf("%f\n",tempFloat);
    return 0;
}

static const shell_command_t shell_commands[] = {
    { "readtemp", "Read the temp from the max31855", _temp_handler },
    { NULL, NULL, NULL }
};

int main(void)
{
    max31855_init(SPI_PORT, SPI_CS_PIN);
    max31855_readtemp(SPI_PORT, SPI_CS_PIN, tempChar);
    float tempFloat = max31855_decodetemp(tempChar);
    printf("%f\n",tempFloat);
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}

/**
    SPI: 
    init
        void    spi_init (spi_t bus)
            Basic initialization of the given SPI bus
        int     spi_init_cs (spi_t bus, spi_cs_t cs)
            Initialize the given chip select pin.
        int     spi_acquire (spi_t bus, spi_cs_t cs, spi_mode_t mode, spi_clk_t clk)
            Start a new SPI transaction.

*/