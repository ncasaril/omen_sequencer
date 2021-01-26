#!/bin/sh

case $1 in
    pre)
        [ -e /usr/local/bin/omen_coloursetup ] && sudo /usr/local/bin/omen_coloursetup 2
        [ -e /usr/local/bin/omen_coloursetup ] && sudo /usr/local/bin/omen_coloursetup 0
        ;;
    post)
        [ -e /usr/local/bin/omen_coloursetup ] && sudo /usr/local/bin/omen_coloursetup 1
    ;;
esac
