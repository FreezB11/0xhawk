#include "tcp.h"
#include <iostream>
#include <vector>

TCPServer::TCPServer(const std::string& ip, int port) : ip(ip), port(port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        exit(EXIT_FAILURE);
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed.\n";
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed.\n";
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

TCPServer::~TCPServer() {
    closesocket(server_socket);
    WSACleanup();
}

void TCPServer::start() {
    std::cout << "Server is listening on " << ip << ":" << port << std::endl;
    while (true) {
        client_socket = accept(server_socket, nullptr, nullptr);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "Accept failed.\n";
            closesocket(server_socket);
            WSACleanup();
            exit(EXIT_FAILURE);
        }

        handleClient(client_socket);
    }
}

void TCPServer::handleClient(SOCKET client_socket) {
    const int buffer_size = 1024;
    char buffer[buffer_size] = {0};
    int bytes_received = recv(client_socket, buffer, buffer_size, 0);
    if (bytes_received > 0) {
        std::cout << "Received: " << buffer << std::endl;

        std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello World!";
        send(client_socket, response.c_str(), response.length(), 0);
    }
    closesocket(client_socket);
}
