#include "SocketIStream.hpp"

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

using namespace server_side;

SocketIStream::SocketIStream(int sockfd) : m_sockfd(sockfd) {}

std::string SocketIStream::readOneLine() const {
    std::string buffer(BUFFER_SIZE, '\0');

    const auto numBytesRead = read(m_sockfd, buffer.data(), buffer.size() - 1);
    if (numBytesRead < 0) {
        //close(sockfd) is handeled in the servers
        THROW_SYSTEM_ERROR();
    }

    buffer[numBytesRead] = '\0';

    return buffer;
}