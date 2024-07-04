all: server

server: obj/main.o obj/tcp.o
	g++ -o build/server obj/main.o obj/tcp.o -lws2_32

main.o: main.cc tcp.h
	g++ -c main.cc

tcp.o: tcp.cc tcp.h
	g++ -c tcp.cc

clean:
	del *.o server.exe
