#include "SocketServer.hpp"

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

using namespace server_side;

SocketServer::SocketServer() {
    writeFileContent(LOG_LOCATION, LOG_TITLE);
}

void SocketServer::start(int port, const std::shared_ptr<ClientHandler> ch) {

    //creating the socket
    const auto sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        THROW_SYSTEM_ERROR();
    }

    //intalizing the sockaddr
    sockaddr_in connectAddress{};
    if (0 == inet_aton("0.0.0.0", &connectAddress.sin_addr)) {
        close(sockfd);
        throw std::runtime_error{"Failed converting IP to 4-bytes"};
    }
    connectAddress.sin_family = AF_INET;
    connectAddress.sin_port = htons(port);

    //binding the socket to the port
    if (0 > bind(sockfd, reinterpret_cast<const sockaddr*>(&connectAddress), 
    sizeof(connectAddress))){
        close(sockfd);
        THROW_SYSTEM_ERROR(); 
    }

    //intalize num of clients to listen to

    if(0 > listen(sockfd, SERVER_BACKLOG)) {
        close(sockfd);
        THROW_SYSTEM_ERROR(); 
    }

    //accepting the clients
    acceptClients(sockfd, ch);

    close(sockfd);
}