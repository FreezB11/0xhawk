all: main.o tcp.o route.o server

server: main.o tcp.o route.o
	g++ -o server src/main.o src/tcp.o route.o -lws2_32

main.o: main.cc src/tcp.h src/route.h
	g++ -c main.cc

tcp.o: src/tcp.cc src/tcp.h src/route.h
	g++ -c src/tcp.cc

route.o: src/route.cc src/route.h
	g++ -c src/route.cc

clean:
	del *.o server.exe
