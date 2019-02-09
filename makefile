all: ok.c
	gcc -o ok ok.c
clean:
	rm ok ok.o
run: ok
	./ok ${want}
