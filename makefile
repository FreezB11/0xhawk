CC= g++ 
LIBS = -lm -LEigen
FILES = src/csv.cc src/cnn.cc src/lib/mmath.cc src/nn.cc

all:
	${CC} -o cnn ${FILES} ${LIBS}
	./cnn

clean:
	rm cnn