CC = gcc
FLAGS = -o 
IFLAGS = -lm
FILES = main.c nn.c matrix.c #lib/calculas.c
# OBJ_FILES = main.o 
OUT_DIR = builds/main
# gcc -o builds/main main.c
#gcc nn.c lib/calculas.c -lm (for math lib) 
# to create obj files
# gcc -Wall -c {filename}.c

nn: ${FILES} 
	${CC} ${FLAGS} ${OUT_DIR} ${FILES} ${IFLAGS}

run: ${OUT_DIR}
	./${OUT_DIR}

print: $(wildcard *.c)
	ls -la  $?