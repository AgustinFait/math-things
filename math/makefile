

main.out: obj/matrices.o obj/main.o obj/funciones.o obj/tree.o obj/node.o obj/console.o
	gcc obj/matrices.o obj/main.o obj/funciones.o obj/tree.o obj/node.o obj/console.o -o bin/ecuaciones

obj/matrices.o: matrices.c
	gcc -c matrices.c -o obj/matrices.o

obj/main.o: main.c
	gcc -c main.c -o obj/main.o

obj/funciones.o: funciones.c
	gcc -c funciones.c -o obj/funciones.o

obj/tree.o: tree.c
	gcc -c tree.c -o obj/tree.o

obj/node.o: node.c
	gcc -c node.c -o obj/node.o

obj/console.o: console.c
	gcc -c console.c -o obj/console.o