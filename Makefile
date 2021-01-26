omen_coloursetup: colour_setup.c colour_setups.h
	gcc -DHAVE_CONFIG_H -g -Wall -O2 -o omen_coloursetup colour_setup.c -lhidapi-hidraw -I /usr/include/hidapi -I./

all: omen_coloursetup

install:
	cp omen_coloursetup /usr/local/bin/
