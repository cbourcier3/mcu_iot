APPLICATION=Lab2

BOARD ?= nucleo-l073rz

USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += xtimer
USEMODULE += periph_gpio_irq
USEMODULE += periph_i2c

FEATURES_REQUIRED += periph_gpio
FEATURES_REQUIRED += periph_i2c
FEATURES_REQUIRED += periph_hwrng
RIOTBASE ?= $(CURDIR)/../../RIOT

DEVELHELP ?= 1

include $(RIOTBASE)/Makefile.include
