CC= g++ 
LIBS = -lm -LEigen
FILES = csv.cc cnn.cc lib/mmath.cc

all:
	${CC} -o cnn ${FILES} ${LIBS}
	./cnn

clean:
	rm cnn