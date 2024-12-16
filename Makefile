test:
	gcc ./tests/*.c -lm -o testsout
	./testsout

run:
	./out

clean:
	rm ./out