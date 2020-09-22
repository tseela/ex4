#include "MySerialServer.hpp"
#include "MyParallelServer.hpp"
#include "ProblemsClientHandler.hpp"
#include <iostream>

using namespace server_side;
using namespace std;

int main() {
    try{
    MyParallelServer server = MyParallelServer();
    const std::shared_ptr<ClientHandler> ch = make_shared<ProblemsClientHandler>();
    server.start(7550, ch);
    } catch (const exception& e) {
        cerr<<e.what()<<endl;
    }
    return 0;
}