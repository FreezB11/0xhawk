#include "src/tcp.h"

int main() {
    TCPServer server("127.0.0.1", 8080);
    server.start();
    return 0;
}
