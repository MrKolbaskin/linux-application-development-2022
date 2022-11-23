CFLAGS = -g -O0
GENERATES = run sed_res esub_res

build: esub.c
	cc $(CFLAGS) $< -o run

test: build
	echo 'afsdkfuqweru2341389' | sed -E 's/[0-9]/Z/' > sed_res
	./run '[0-9]' 'Z' 'afsdkfuqweru2341389' > esub_res
	cmp sed_res esub_res

	echo 'aaabbbcccababccabb' | sed -E 's/ab//' > sed_res
	./run 'ab' '' 'aaabbbcccababccabb' > esub_res
	cmp sed_res esub_res

	@echo 'Tests passed'

clean:
		rm -rf $(GENERATES)
