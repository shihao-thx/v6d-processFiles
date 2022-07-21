#include <iostream>
#include <memory>


// we need a global reference of the server_ptr to do cleanup
static std::shared_ptr<vineyard::VineyardRunner> server_runner_ = nullptr;

int main() {

    return 0;
}