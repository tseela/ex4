#include "SocketIStream.hpp"

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

using namespace server_side;

SocketIStream::SocketIStream(int sockfd) : m_sockfd(sockfd), m_isSecceded(false) {
    m_line = STRING_TIMEOUT;
}

std::string SocketIStream::readOneMassege() {
    m_isSecceded = false;
    m_line = STRING_TIMEOUT;
    m_tRead = std::thread(&SocketIStream::tryToRead, this);
    m_tStop = std::thread(&SocketIStream::stop, this);
    m_tRead.join();
    m_tStop.join();

    if (m_tExp) {
        std::rethrow_exception(m_tExp);
    }
    return m_line.data();
}

void SocketIStream::tryToRead() {
    try{
        std::string buffer(BUFFER_SIZE, '\0');

        const auto numBytesRead = read(m_sockfd, buffer.data(), buffer.size() - 1);
        m_isSecceded = true;
        if (numBytesRead < 0) {
            //close(sockfd) is handeled in the servers
            THROW_SYSTEM_ERROR();
        }

        buffer[numBytesRead] = '\0';

        m_line = buffer;
    } catch (const std::exception& e) {
        m_tExp = std::current_exception();
    }

    if (0 != pthread_cancel(m_tStop.native_handle())) {
        THROW_SYSTEM_ERROR(); 
    }
}

void SocketIStream::stop() {
    std::this_thread::sleep_for(READ_TIMEOUT);

    if(!m_isSecceded) {
        if (0 != pthread_cancel(m_tRead.native_handle())) {
            THROW_SYSTEM_ERROR(); 
        }

        
        std::unique_ptr<SocketOStream> out = std::make_unique<SocketOStream>(m_sockfd);
        out->writeOneMassege(SocketOStream::NO_RESPONSE, SocketOStream::TIMEOUT_HAS_PASSED);

        std::string contant = readFileContent(FILE_TO_NOTIFY);
        writeFileContent(FILE_TO_NOTIFY, contant + "Timeout has past, Client disconnected\n");
    }
}