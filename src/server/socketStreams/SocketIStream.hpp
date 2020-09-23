#pragma once

#include <unistd.h>

#include <string>
#include <system_error>
#include <chrono>
#include <atomic>
#include <exception>
#include <pthread.h>
#include <thread>

namespace server_side {
    class SocketIStream {
        int m_sockfd;
        std::atomic_bool m_isSecceded; //used by two threads
        std::string m_line;
        std::exception_ptr m_tExp = nullptr;
        std::thread m_tRead;

        public:
            static constexpr auto BUFFER_SIZE = 1024;
            static constexpr std::string_view STRING_TIMEOUT= "";
            static constexpr std::chrono::seconds READ_TIMEOUT = std::chrono::seconds(5);

            explicit SocketIStream(int sockfd);
            std::string readOneLine();

        private:
            void stop();
            void tryToRead();
    };
}