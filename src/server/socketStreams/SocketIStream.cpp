#include "SocketIStream.hpp"

#define THROW_SYSTEM_ERROR() \
    throw std::system_error { errno, std::system_category() }

#define TIMOUT_ERROR() throw std::runtime_error("Timeout has past, Client disconnected\n")

using namespace server_side;

SocketIStream::SocketIStream(int sockfd) : m_sockfd(sockfd), m_isSecceded(false) {
    m_line = START_STRING;
}

std::string SocketIStream::readOneMassege() {
    m_isSecceded = false;
    m_line = START_STRING;

    //try to read
    m_tRead = std::thread(&SocketIStream::tryToRead, this);

    //stops if timeout have passed
    m_tStop = std::thread(&SocketIStream::stop, this);

    m_tRead.join();
    m_tStop.join();

    if (m_tExp) {//throw exption if neede
        std::rethrow_exception(m_tExp);
    }

    //throws timeout
    if(!m_isSecceded) {
        TIMOUT_ERROR();
    }
    return m_line.data();
}

void SocketIStream::tryToRead() {
    try{
        while(!massegeEnd()) {
            m_isSecceded = false;
            std::string buffer(BUFFER_SIZE, '\0');

            //reading from the client
            const auto numBytesRead = read(m_sockfd, buffer.data(), buffer.size() - 1);
            m_isSecceded = true;
            if (numBytesRead < 0) {
                //close(sockfd) is handeled in the servers
                THROW_SYSTEM_ERROR();
            }

            buffer[numBytesRead] = '\0';
            
            std::string copy = buffer;
            m_line += copy.data();
        }
    } catch (const std::exception& e) {
        m_tExp = std::current_exception();
    }

    //if succedd stops the timeout counter
    if (0 != pthread_cancel(m_tStop.native_handle())) {
        THROW_SYSTEM_ERROR(); 
    }
}

void SocketIStream::stop() {
    std::this_thread::sleep_for(READ_TIMEOUT);

    //if not read the messege.
    if(!m_isSecceded) {
        if (0 != pthread_cancel(m_tRead.native_handle())) {
            THROW_SYSTEM_ERROR(); 
        }

        //writes to client timeout has passed.
        std::unique_ptr<SocketOStream> out = std::make_unique<SocketOStream>(m_sockfd);
        out->writeOneMassege(SocketOStream::NO_RESPONSE, SocketOStream::TIMEOUT_HAS_PASSED);
    }
}

bool SocketIStream::massegeEnd() const{

    return m_line.size() >= END_MASSEGE_LENTGH &&
     0 == m_line.compare(m_line.size()-END_MASSEGE_LENTGH, END_MASSEGE_LENTGH, END_MASSEGE);
}