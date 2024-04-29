build:
	gcc ./src/*.c -o out

run:
	./out

clean:
	rm ./out