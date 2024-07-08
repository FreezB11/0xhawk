all: server

server: main.o tcp.o
	g++ -o build/server obj/*.o -lws2_32

main.o: main.cc src/tcp.h
	g++ -o obj/main.o -c main.cc 

tcp.o: src/tcp.cc src/tcp.h
	g++ -o obj/tcp.o -c src/tcp.cc

clean:
	del *.o server.exe
