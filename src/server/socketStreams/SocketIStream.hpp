#pragma once

#include "file_reading.hpp"
#include "SocketOStream.hpp"

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
        std::thread m_tStop;

        public:
            static constexpr auto TIMEOUT_FAILED = "Timeout has past, Client disconnected\n";
            static constexpr auto FILE_TO_NOTIFY = "SERVER_LOG.txt";
            static constexpr auto BUFFER_SIZE = 1024;
            static constexpr auto START_STRING = "";
            static constexpr std::chrono::seconds READ_TIMEOUT = std::chrono::seconds(5);

            explicit SocketIStream(int sockfd);
            std::string readOneMassege();

        private:
            void stop();
            void tryToRead();
    };
}