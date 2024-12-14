test:
	gcc ./tests/*.c -o testsout
	./testsout

run:
	./out

clean:
	rm ./out