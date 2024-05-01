CC = gcc

SRC = main.c diccionario.c

TARGET = diccionario

all:
	${CC} ${SRC} -o ${TARGET}.out

clear:
	rm *[^\.c][^\.h][^\(Makefile\)]