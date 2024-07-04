#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

class TCPServer {
public:
    TCPServer(const std::string& ip, int port);
    ~TCPServer();
    void start();

private:
    SOCKET server_socket;
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    int port;
    std::string ip;
    void handleClient(SOCKET client_socket);
};

#endif
