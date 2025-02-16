CC= g++ 
LIBS = -lm -LEigen
FILES = nn.cc ../src/lib/mmath.cc

all:
	${CC} -o nn ${FILES} ${LIBS}
	./nn

clean:
	rm nn

test:
	${CC} -o test test.cc ${LIBS}
	./test
