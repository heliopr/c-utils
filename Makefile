buildtest: $(wildcard tests/*.c)
	gcc $^ -Wall -lm -O0 -o test

test: buildtest
	./test

clean:
	rm ./test