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

class RedisMetaService : public std::enable_shared_from_this<RedisMetaService> {
public:
    /* redis 不能构造redis_ 改为引用*/
    RedisMetaService(std::unique_ptr<AsyncRedis>& redis)
        : redis_(redis) /*, worker(meta_context_) */{}
    void commitUpdates(unsigned);
private:
    std::unique_ptr<AsyncRedis>& redis_;
};

void RedisMetaService::commitUpdates(unsigned j) {
	redis_->command<long long>("SETNX", "redis_revision", 0).get();
	string prefix_ = "vineyard/";
	// produce kvs
    vector<ops> changes;
    for(int i=j; i<j+3; i++) {
        ops op{.key="key_" + to_string(i), .val = "value_" + to_string(i), .type = i};
        changes.emplace_back(op);
        /*
        changes.emplace_back(ops{.key=1, .val=i+1});
        */
    }
/*
	auto self(shared_from_this());
    redis_->command<long long>("SETNX", "redis_revision", 0,
	  [self](Future<long long> &&resp) {
		self->redis->command<long long>("incr", "redis_revision",
		  [self](Future<long long> &&resp) {
			
		  });
	  });*/
    //async_redis.incr("redis_revision").get();
	/*async_redis.command<long long>("incr", "redis_revision",
	  [](Future<long long> &&resp) {
		
	  });*/
	
	/* incr 不能放在这里 */
	//redis_->incr("redis_revision").get();
    auto rev = *(redis_->get("redis_revision").get());
    auto opt_prefix = "op:" + rev;

    //unordered_map<string, string> kvs;
	std::vector<string> kvs;
	kvs.emplace_back("MSET");

    unordered_map<string, unsigned> opts;
    vector<string> ks;
	
    for(auto& op : changes) {
        if(op.type % 2 == 0) { // put
            //kvs.insert({prefix_ + op.key, op.val});
			kvs.emplace_back(prefix_ + op.key);
			kvs.emplace_back(op.val);
            opts.insert({op.key, 0}); // push
        } else { // del
        /*std::string op_key = boofst::algorithm::erase_head_copy(
            op.kv.key, prefix_.size());*/
            ks.emplace_back(prefix_ + op.key);
            opts.insert({op.key, 1});
        }
    }

	//kvs.emplace_hint(kvs.begin(), "mset", "");
	
    redis_->del(ks.begin(), ks.end(),
	  [](Future<long long> &&resp) {
			
	  });
	auto self(shared_from_this());
    redis_->command<void>(kvs.begin(), kvs.end(),
	  [self, opts, opt_prefix, rev](Future<void> &&resp) {
		self->redis_->hset(opt_prefix, opts.begin(), opts.end(),
		  [self, opt_prefix, rev](Future<long long> &&resp) {
			self->redis_->command<long long>("rpush", "optlist", opt_prefix,
			  [self, rev](Future<long long> &&resp) {
				self->redis_->command<long long>("incr", "redis_revision",
				  [self, rev](Future<long long> &&resp) {
					self->redis_->command<long long>("publish", "opts", rev,/*不加1了，sub的不减1*/
					  [](Future<long long> &&resp) {

					  });
				  });
			  });
		  });
	  });

    //async_redis.hmset(opt_prefix, opts.begin(), opts.end()).get();
    //async_redis.rpush("optlist", opt_prefix).get();
    //async_redis.publish("opts", rev).get();
}

int main() {
	ConnectionOptions opts;
    opts.host = "192.168.127.130";
    opts.password = "root";
    opts.port = 6379;

    ConnectionPoolOptions pool_opts;
    pool_opts.size = 3;

    std::unique_ptr<AsyncRedis> redis_client;
    redis_client.reset(new AsyncRedis(opts, pool_opts));

    Future<std::string> ping_res = redis_client->ping();
    if(ping_res.get() == "PONG") {
        cout << "hello redis" << endl;
    }
	
	shared_ptr<RedisMetaService> redis_ptr = make_shared<RedisMetaService>(redis_client);

	redis_ptr->commitUpdates(1);
	cin.get(); // 加锁
	redis_ptr->commitUpdates(4);
	cin.get();

	redis_ptr->commitUpdates(7);
	cin.get();
	redis_ptr->commitUpdates(10);

	cin.get();

	return 0;
}
