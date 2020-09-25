#include "SocketOStream.hpp"

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

using namespace server_side;

SocketOStream::SocketOStream(int sockfd) : m_sockfd(sockfd) {}

void SocketOStream::writeOneMassege(std::string output,
     std::uint32_t status /*=0 - success*/) const {
    //creating the massege
    std::string massege = "Version: ";
    massege += SERVER_VERSION;
    massege += BREAK_LINE;
    massege += "status: ";
    massege += std::to_string(status);
    massege += BREAK_LINE;
    massege += "response-length: ";
    massege += std::to_string(output.size());
    massege += BREAK_LINE;
    massege += BREAK_LINE;
    massege += output;


    //sending the messege
    if (write(m_sockfd, massege.data(), massege.length()) < 0) {
        //close(sockfd) is handeled in the servers
        THROW_SYSTEM_ERROR();
    }
}