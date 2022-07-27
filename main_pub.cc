#include <redis++/async_redis++.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <iterator>
#include <unordered_map>

using namespace sw::redis;
using namespace std;

struct ops {
    string key;
    string val;
	unsigned type;
};

void commitUpdates(AsyncRedis& async_redis, unsigned j) {
	string prefix_ = "vineyard/";
    async_redis.command<long long>("SETNX", "redis_revision", 0).get();

	// produce kvs
    vector<ops> changes;
    for(int i=j; i<j+3; i++) {
        ops op{.key="key_" + to_string(i), .val = "value_" + to_string(i), .type = i};
        changes.emplace_back(op);
        /*
        changes.emplace_back(ops{.key=1, .val=i+1});
        */
    }

    async_redis.incr("redis_revision").get();
    auto rev = *async_redis.get("redis_revision").get();
    auto opt_prefix = "op:" + rev;

    unordered_map<string, string> kvs;
    unordered_map<string, unsigned> opts;
    vector<string> ks;

    for(auto& op : changes) {
        if(op.type % 2 == 0) {
            kvs.insert({prefix_ + op.key, op.val});
            opts.insert({op.key, 0}); // push
        } else {
        /*std::string op_key = boofst::algorithm::erase_head_copy(
            op.kv.key, prefix_.size());*/
            ks.emplace_back(prefix_ + op.key);
            opts.insert({op.key, 1});
        }
    }

    async_redis.mset(kvs.begin(), kvs.end()).get();
    async_redis.del(ks.begin(), ks.end()).get();

    async_redis.hmset(opt_prefix, opts.begin(), opts.end()).get();
    async_redis.rpush("optlist", opt_prefix).get();
    async_redis.publish("opts", rev).get();
}

int main() {
    ConnectionOptions opts;
    opts.host = "192.168.127.130";
    opts.password = "root";
    opts.port = 6379;

    ConnectionPoolOptions pool_opts;
    pool_opts.size = 1;
    auto async_redis = AsyncRedis(opts, pool_opts);

    Future<std::string> ping_res = async_redis.ping();
    if(ping_res.get() == "PONG") {
        cout << "hello redis" << endl;
    }
	
	commitUpdates(async_redis, 1);
	commitUpdates(async_redis, 4);


	cin.get();

	return 0;
}
