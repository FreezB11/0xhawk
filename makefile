CC= g++ 
LIBS = -lm -LEigen

all:
	${CC} -o cnn cnn.cc ${LIBS}

clean:
	rm cnn