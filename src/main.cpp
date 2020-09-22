#include "MySerialServer.hpp"
#include "ProblemsClientHandler.hpp"
#include <iostream>

using namespace server_side;
using namespace std;

int main() {
    try{
    MySerialServer server = MySerialServer();
    const std::shared_ptr<ClientHandler> ch = make_shared<ProblemsClientHandler>();
    server.open(8888, ch);
    } catch (const exception& e) {
        cerr<<e.what()<<endl;
    }
    return 0;
}