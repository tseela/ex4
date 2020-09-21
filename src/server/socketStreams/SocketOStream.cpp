#include "SocketOStream.hpp"

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

using namespace server_side;

SocketOStream::SocketOStream(int sockfd) : m_sockfd(sockfd) {}

void SocketOStream::writeOneLine(std::string output) const {
    if (write(m_sockfd, output.data(), output.length()) < 0) {
        //close(sockfd) is handeled in the servers
        THROW_SYSTEM_ERROR();
    }
}