

main.out: obj/matrices.o obj/main.o 
	gcc obj/matrices.o obj/main.o -o bin/ecuaciones

obj/matrices.o: matrices.c
	gcc -c matrices.c -o obj/matrices.o

obj/main.o: main.c
	gcc -c main.c -o obj/main.o
