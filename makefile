CC= g++ 
CFLAGS = -std=c++23 -O3
LIBS = -lm -LEigen

# find all the .cc files
cc = $(wildcard ./src/*.cc)
# convert the .cc files to .o files
obj = ${cc:.cc=.o}
# find all the .h files
h = $(wildcard ./src/*.h)

all: ${obj}
	${CC} ${CFLAGS} main.cc ${obj} -o main ${LIBS}

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $< to $@"

clean:
	rm -f *.obj
	rm -f main
	clear