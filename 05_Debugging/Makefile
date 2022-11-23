GENERATES = run *out
CFLAGS = -g -O0

DBFLAGS = --batch --quiet

build: range.c
	cc $(CFLAGS) range.c -o run

test: build
	gdb $(DBFLAGS) --command=script1.gdb --args ./run | grep '^@@@' | cut -c 4- > script1_out
	gdb $(DBFLAGS) --command=script2.gdb --args ./run | grep '^@@@' | cut -c 4- > script2_out
	cmp script1_out script1_answer
	cmp script2_out script2_answer
	@echo "Tests passed"

clean:
	rm -rf $(GENERATES)

