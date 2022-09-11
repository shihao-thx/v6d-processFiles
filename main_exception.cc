#include "redis++/async_redis++.h"
#include "redis++/redis++.h"
#include <iostream>
#include <string>

using namespace sw::redis;
using namespace std;

void test01(std::unique_ptr<AsyncRedis>& redis_client) {
    try {
        auto ping_res = redis_client->ping();
        auto respinse = ping_res.get();
        cout << "start3 test01" << endl;
        if(respinse == "PONG") {
            cout << "hello redis" << endl;
        }  
    } catch (...) {
        cout << "exception happened." << endl;
    } 
    cout << "end test01" << endl;
}

int main() {
	ConnectionOptions opts;
    opts.host = "192.168.127.135";
    opts.socket_timeout = std::chrono::seconds(10);
    opts.port = 6379;

    ConnectionPoolOptions pool_opts;
    pool_opts.size = 3;
    //pool_opts.connection_lifetime = std::chrono::milliseconds(1000);
    //pool_opts.wait_timeout = std::chrono::milliseconds(100);

    std::unique_ptr<AsyncRedis> redis_client;
    redis_client.reset(new AsyncRedis(opts, pool_opts));

    std::unique_ptr<Redis> syncredis_client;
    syncredis_client.reset(new Redis(opts, pool_opts));

    test01(redis_client);

    cin.get();

	return 0;
}
