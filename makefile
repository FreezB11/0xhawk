CC= g++ 
CFLAGS =-Ihawk/include -std=c++23 -O3 -mavx2 -mfma -ffast-math -Wall -Wextra -fPIC
LIBS = -lm -LEigen
HOME = /hawk
# find all the .cc files
cc = $(wildcard .${HOME}/src/*.cc) ${wildcard .${HOME}/src/lib/*.cc}
# convert the .cc files to .o files
obj = ${cc:.cc=.o}

libname = libhawk.so
libpath = /usr/local/lib
incpath = /usr/local/include/hawk

# find all the .h files
h = $(wildcard ./src/*.h)

all: ${obj}
	${CC} ${CFLAGS} main.cc ${obj} -o build/main ${LIBS}

# Rule to create the shared library
$(libname): $(obj)
	@echo "Creating shared library $@"
	$(CC) -shared -o $@ $(obj) $(LIBS)

%.o: %.cc
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) -c $< -o $@

# install:
# 	@echo "Installing shared library to $(libpath)"
# 	@sudo cp $(libname) $(libpath)
# 	@sudo ldconfig
# 	@echo "Installing header files to $(incpath)"
# 	@sudo mkdir -p $(incpath)
# 	@sudo cp /home/doc/ml/hawk/hawk/include/hawk/*.h $(incpath)
# 	@echo "Installation complete."

clean:
	rm -f hawk/src/*.o hawk/src/lib/*.o
	rm -f build/main
	clear