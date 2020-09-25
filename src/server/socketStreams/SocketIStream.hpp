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
            static constexpr auto END_MASSEGE = "\r\n\r\n";
            static constexpr auto END_MASSEGE_LENTGH = 4;
            static constexpr std::chrono::seconds READ_TIMEOUT = std::chrono::seconds(5);

            /**
             * @brief Construct a new Socket I Stream object.
             * 
             * @param sockfd of the client connection.
             */
            explicit SocketIStream(int sockfd);

            /**
             * @brief Reading one massege from the client.
             * 
             * @return std::string the massege.
             */
            std::string readOneMassege();

        private:
            /**
             * @brief stops the reading if the timeout has pased.
             * 
             */
            void stop();

            /**
             * @brief trying to read the massege.
             * 
             */
            void tryToRead();

            bool massegeEnd() const;
    };
}