#include <redis++/redis++.h>
#include <redis++/async_redis++.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace sw::redis;
int main() {
// connect to the redis server formed by three instances
    auto redis = Redis("tcp://root@192.168.127.130:6379");
    while(1) {
        // get key-value in loop
        auto val = redis.get("key");
        if(val) {
            std::cout<<"key : "<<*val<<std::endl;
        } else {
            std::cout<<"key doesn't exist."<<std::endl;
        }
        sleep(5);
    }
    return 0;
}
