CC= g++ 
LIBS = -lm -LEigen

all:
	${CC} -o cnn cnn.cc ${LIBS}
	./cnn

clean:
	rm cnn