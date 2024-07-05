all: server

server: main.o tcp.o
	g++ -o build/server main.o tcp.o -lws2_32

main.o: main.cc src/tcp.h
	g++ build/ -c main.cc 

tcp.o: src/tcp.cc src/tcp.h
	g++ -c src/tcp.cc

clean:
	del *.o server.exe
