#pragma once

#include <unistd.h>

#include <string>
#include <system_error>

namespace server_side {
    class SocketOStream {
        int m_sockfd;

        public:
        explicit SocketOStream(int sockfd);
        void writeOneLine(std::string output) const;
    };
}