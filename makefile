all: ok.c
	gcc -o ok ok.c
clean:
	rm ok ok.c README.txt makefile
run: ok
	./ok '${want}'
