#include "MySerialServer.hpp"
#include "MyParallelServer.hpp"
#include "Server.hpp"
#include "ProblemsClientHandler.hpp"

#include <exception>
#include <memory>
#include <iostream>
#include <string.h>

using namespace server_side;

int main(int argc, const char *argv[]) {
    try{
        // first arg is ex4.out and we don't need it
        auto startIndex = 1;
        --argc;

        if(argc != 2 && argc != 1) {
            throw std::runtime_error("Expecting to 2 or 1 arguments");
        }

        std::unique_ptr<Server> server;
        std::shared_ptr<ProblemsClientHandler> probCH = std::make_unique<ProblemsClientHandler>();

        auto port = 0;

        try{
            port = std::stoi(argv[startIndex]);
        } catch (const std::exception& e) {
            throw std::runtime_error("The first argument should be int that represents the port of the server");
        }

        if(port < 1024 || port > 49151) { //the server ports are between 1024-49151
            throw std::runtime_error("The port for server should be between 1024-49151");
        }

        if(argc == 2) {
            if(strcmp(argv[startIndex + 1], "parallel") == 0) {
                server = std::make_unique<MyParallelServer>();
            } else if(strcmp(argv[startIndex + 1], "serial") == 0) {
                server = std::make_unique<MySerialServer>();
            } else {    
                throw std::runtime_error("The server argument can only be: parallel or serial");
            }
        } else {
            server = std::make_unique<MyParallelServer>();
        }

        server->start(port, probCH);
    } catch (const std::exception& e) {
        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}