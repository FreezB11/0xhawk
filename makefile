CC= g++ 
CFLAGS =-Ihawk/include -std=c++23 -O3 -mavx2 -mfma -ffast-math -Wall -Wextra
LIBS = -lm -LEigen
HOME = /hawk
# find all the .cc files
cc = $(wildcard .${HOME}/src/*.cc) ${wildcard .${HOME}/src/lib/*.cc}
# convert the .cc files to .o files
obj = ${cc:.cc=.o}
# find all the .h files
h = $(wildcard ./src/*.h)

all: ${obj}
	${CC} ${CFLAGS} main.cc ${obj} -o build/main ${LIBS}

%.o: %.cc
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o src/lib/*.o
	rm -f build/main
	clear