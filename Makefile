all: main.o grafo.o
	@gcc main.o grafo.o -o exe
	@rm *.o
main.o: main.c
		@gcc main.c -c
grafo.o: grafo.c
	@gcc grafo.c -c
run:
	@./exe