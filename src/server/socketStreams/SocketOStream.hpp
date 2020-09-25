#pragma once

#include <unistd.h>

#include <string>
#include <cstdint>
#include <system_error>

namespace server_side {
    class SocketOStream {
        int m_sockfd;

        public:
            static constexpr auto SERVER_VERSION = "1.0";
            static constexpr auto BREAK_LINE = "\r\n";
            static constexpr auto BREAK_LINE_SIZE = 2;
            
            static constexpr auto NO_RESPONSE = "";
            static constexpr auto NOT_ENOUGH_ARG = 1;
            static constexpr auto NOT_SUPPORTED_PROBLEM = 2;
            static constexpr auto TIMEOUT_HAS_PASSED = 3;
            static constexpr auto NOT_SUPPORTED_ALG = 4;
            static constexpr auto MISSING_ROW = 5;
            static constexpr auto NO_INT_ROW_WITH_TWO_VALUES = 6;
            static constexpr auto INVALID_MATRIX_VALUE = 7;
            static constexpr auto NUM_VALUES_NOT_EQUALS_MATRIX_WIDTH = 8;
            static constexpr auto VALUE_MUST_BE_POSITIVE = 9;
            static constexpr auto MISSING_ROW_WITH_TWO_VALUES = 10;

            /**
             * @brief Construct a new Socket O Stream object.
             * 
             * @param sockfd of the client connection.
             */
            explicit SocketOStream(int sockfd);

            /**
             * @brief writes one massege.
             * 
             * @param output the rsponse to the client.
             * @param status the massege status.
             */
            void writeOneMassege(std::string output, std::uint32_t status = 0) const;
    };
}