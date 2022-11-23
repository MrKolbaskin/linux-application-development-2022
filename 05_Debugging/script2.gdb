set pagination off
set logging file gdb2.out
set logging on

set $count = 0

break range.c:15 if ($count++ >= 27 && $count <= 35)
    command 1
    echo @@@
    printf "%d\n", i
    continue
end

run -100 100 3 > /dev/null

set logging enabled off
quit
