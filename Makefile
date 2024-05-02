CC = gcc

SRC = main.c diccionario.c

TARGET = a

all:
	${CC} ${SRC} -o ${TARGET}.out

clear:
	rm *[^\.c][^\.h][^\(Makefile\)]