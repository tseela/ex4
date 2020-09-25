#include "file_reading.hpp"

#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <mutex>
#include <fstream>
#include <string_view>
#include <thread>
#include <system_error>
#include <vector>
#include <chrono>

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

std::mutex lock;

void open_socket_and_send(int port, int ClientsIndex) {
    auto fileName = std::to_string(ClientsIndex) + ".txt";
    std::unique_lock<std::mutex> gaurd(lock);
    std::cout<<fileName<<std::endl;
    gaurd.unlock();
    files::writeFileContent("serverMassege/" + fileName, "");

    const auto sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        THROW_SYSTEM_ERROR();
    }

    sockaddr_in connectAddress{};
    if (0 == inet_aton("127.0.0.1", &connectAddress.sin_addr)) {
        close(sockfd);
        throw std::runtime_error{"Failed converting IP to 4-bytes"};
    }
    connectAddress.sin_family = AF_INET;
    connectAddress.sin_port = htons(port);

    if (0 > connect(sockfd, reinterpret_cast<const sockaddr*>(&connectAddress),
                                    sizeof(connectAddress))) {
        close(sockfd);
        THROW_SYSTEM_ERROR();
    }

    int numOfLine = 0;
    std::ifstream input("clients/" + fileName);
    for(std::string line; getline( input, line );){
        try{
            numOfLine++;
            line += "\r\n";
            if (write(sockfd, line.data(), line.length()) < 0) {
                close(sockfd);
                THROW_SYSTEM_ERROR();
            }

            if(numOfLine == 2) {
                std::string buffer(1024, '\0'); 
                const auto numBytesRead = read(sockfd, buffer.data(), buffer.size() - 1);
                if (numBytesRead < 0) {
                    close(sockfd);
                    THROW_SYSTEM_ERROR();
                }
                buffer[numBytesRead] = '\0';

                std::string contant = files::readFileContent("serverMassege/" + fileName);
                files::writeFileContent("serverMassege/" + fileName, contant + buffer.data());
            }

        } catch(...) {//if the server closed the connection
            break;
        }
    }

    while(true){
        std::string buffer(1024, '\0'); 
        const auto numBytesRead = read(sockfd, buffer.data(), buffer.size() - 1);
        if (numBytesRead < 0) {
            close(sockfd);
            break; //the server closed the socket
        }
        buffer[numBytesRead] = '\0';

        if(numBytesRead == 0){
            break;
        }

        std::string contant = files::readFileContent("serverMassege/" + fileName);
        files::writeFileContent("serverMassege/" + fileName, contant + buffer.data());
    }
                    
    close(sockfd);
}

int main() {
    auto port = 1028;
    auto numOfClientsToTest = 9;

    std::vector<std::thread> threads;
    try {
    for(auto i = 0; i < numOfClientsToTest; ++i) {
        threads.push_back(std::thread(open_socket_and_send,port,i));
    }

    for(std::thread &oneThread : threads) {
        oneThread.join();
    }

    } catch (std::system_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}