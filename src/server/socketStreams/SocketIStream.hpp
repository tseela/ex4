#pragma once

#include <unistd.h>

#include <string>
#include <system_error>

namespace server_side {
    class SocketIStream {
        int m_sockfd;

        public:
        static constexpr auto BUFFER_SIZE = 1024;

        explicit SocketIStream(int sockfd);
        std::string readOneLine() const;
    };
}