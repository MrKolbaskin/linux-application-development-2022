GENERATES = prog prog-a prog-so

GREEN = \033[0;32m
NC = \033[0m

all: prog prog-a prog-so

prog: const.o fun.o prog.o
	cc const.o fun.o prog.o -o prog

%.o: %.c
	cc $< -c -o $@

prog-a: prog.o build-liboutput_static.a
	cc liboutput_static.a prog.o -o prog-a

prog-so: prog.o build-liboutput.so
	cc liboutput.so prog.o -o prog-so

build-liboutput_static.a: const.o fun.o
	ar -rcs liboutput_static.a const.o fun.o

build-liboutput.so: const.o fun.o
	cc -shared fun.o const.o -o liboutput.so

.test-%: %
	./$< > out-$<-empty.txt
	./$< arg1 > out-$<-1-argument.txt
	./$< arg1 arg2 arg3 > out-$<-3-arguments.txt
	@ echo

.cmp-outputs:
	cmp out-prog-empty.txt out-prog-a-empty.txt
	cmp out-prog-a-empty.txt out-prog-so-empty.txt
	cmp out-prog-so-empty.txt out-prog-empty.txt
	cmp out-prog-1-argument.txt out-prog-a-1-argument.txt
	cmp out-prog-a-1-argument.txt out-prog-so-1-argument.txt
	cmp out-prog-so-1-argument.txt out-prog-1-argument.txt
	cmp out-prog-3-arguments.txt out-prog-a-3-arguments.txt
	cmp out-prog-a-3-arguments.txt out-prog-so-3-arguments.txt
	cmp out-prog-so-3-arguments.txt out-prog-3-arguments.txt

test: .test-prog .test-prog-a .test-prog-so .cmp-outputs
	@ echo
	@ echo "${GREEN}[tests passed]${NC}"

clean:
	rm -f ${GENERATES} *.o *.a *.so *.txt
