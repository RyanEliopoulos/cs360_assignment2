all: ok.c ok.h
	gcc -o ok ok.c
clean:
	rm ok ok.c
run:
