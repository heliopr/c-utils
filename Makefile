buildtest: $(wildcard tests/*.c)
	gcc $^ -Wall -Werror -lm -O0 -o test

test: buildtest
	./test

clean:
	rm ./test