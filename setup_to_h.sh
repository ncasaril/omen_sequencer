#!/bin/bash

input=$1
output=$2

if [ -z "$output" ];then
    echo "usage: $0 <input> <output.h>"
    exit 2
fi

tmp=$(tempfile)
tmp2=$(tempfile)

[ -e $output ];rm -f $output
echo "const uint8_t mode[][64] = {" >> $output

cat $input|while read -r line
do
    if echo $line|egrep -e "^0000";then
        rm -f $tmp
    fi
    echo $line >> $tmp
    if echo $line|egrep -e "^0070";then
        xxd -r $tmp $tmp2
        echo "    {" >> $output
        cat $tmp2 | xxd -i -c 16|tail -4 >> $output
        echo "    }," >> $output
        echo $tmp
    fi

done < $input
echo "};" >> $output
