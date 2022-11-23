set pagination off
set logging file gdb1.out
set logging on

break range.c:15 if i % 5 == 0
	command 1
	echo @@@
	printf "%d\n", i
	continue
end

run 1 12 > /dev/null

set logging enabled off
quit
