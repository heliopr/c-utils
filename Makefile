test:
	gcc ./tests/*.c -lm -O0 -o testsout
	./testsout

run:
	./out

clean:
	rm ./out