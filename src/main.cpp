#include "MySerialServer.hpp"
#include "ClientHandler.hpp"
#include <iostream>

using namespace server_side;
using namespace std;

int main() {
    try{
    MySerialServer server = MySerialServer();
    const std::shared_ptr<ClientHandler> ch (nullptr);
    server.open(2211, ch);
    } catch (const exception& e) {
        cerr<<e.what()<<endl;
    }
    return 0;
}