#!/bin/sh

# Reset keyboard colours to mode 1

case "$1" in
	resume|thaw)
        [ -e /usr/local/bin/omen_coloursetup ] && sudo /usr/local/bin/omen_coloursetup 1
		;;
esac
