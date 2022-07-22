#include <iostream>
#include <memory>
#include <string>
#include "server/server/vineyard_runner.h"


// we need a global reference of the server_ptr to do cleanup
static std::shared_ptr<vineyard::VineyardRunner> server_runner_ = nullptr;

int main() {
    std::string spec = "redis";
    server_runner_ = vineyard::VineyardRunner::Get(spec); 
    auto status = server_runner_->Serve();
    return 0;
}