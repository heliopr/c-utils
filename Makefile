build:
	gcc ./src/*.c ./src/ds/*.c -o out

run:
	./out

clean:
	rm ./out