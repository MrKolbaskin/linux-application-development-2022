#!/bin/bash
SPACE='20'
NEW_LINE='0a'

DEFAULT_PRINT_DELAY=0.05

cur_col=0
cur_line=0
chars=""

text=$(cat - |od -An -v -t x1)

echo -e $text

for chr in $text; do
    if [[ $chr = $NEW_LINE ]]; then
        cur_line=$((cur_line+1))
        cur_col=0
    elif [[ $chr = $SPACE ]]; then
        cur_col=$((cur_col+1))
    else
        chars="${chr} ${cur_col} ${cur_line}\n${chars}"
        cur_col=$((cur_col+1))
    fi
done

last_line=$cur_line
print_delay="${1:-$DEFAULT_PRINT_DELAY}"

tput clear
echo -en $chars | shuf |
while read -r tmp_c tmp_col tmp_line; do
    tput cup $tmp_line $tmp_col
    echo -ne "\x${tmp_c}"
    sleep $print_delay
done

tput cup $((last_line)) 0