#include <stdio.h>
#include "shell.h"
#include "board.h"

int _target_handler(int argc, char **argv)
{
    (void) argc;
    (void) argv;
	 
	switch (*argv[1]) { 
    case 'B' : 
    	printf("You are running RIOT on a(n) %s board.\n", RIOT_BOARD);
    break; 
    case 'M' : 
		printf("This board features a(n) %s MCU.\n", RIOT_MCU);
    break; 
		default: printf("Illegal code, enter B for Board info or M for MCU info\n"); 
    break;
	}
		
    return 0;
}

int _led_handler(int argc, char **argv)
{
    (void) argc;
    (void) argv;
     
    switch (*argv[1]) { 
    case '1' : 
        LED0_ON;
    break; 
    case '0' : 
        LED0_OFF;
    break; 
    case 't' : 
        LED0_TOGGLE;
    break; 
        default: printf("Illegal code, enter 0 to switch OFF, 1 to switch ON and t to switch into toggle mode\n"); 
    break;
    }
        
    return 0;
}


static const shell_command_t shell_commands[] = {
    { "target", "get target device", _target_handler },
    { "led", "change the state of a LED", _led_handler },
    { NULL, NULL, NULL }
};

int main(void)
{
    gpio_init(LED0_PIN, GPIO_OUT);
	char line_buf[SHELL_DEFAULT_BUFSIZE];
	shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
	return 0;	
}



