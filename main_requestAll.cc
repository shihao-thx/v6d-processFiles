#include <redis++/async_redis++.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <iterator>
#include <unordered_map>
#include <functional>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include<boost/algorithm/string.hpp>

using namespace sw::redis;
using namespace std;
using namespace boost::asio;

/* cannot put in class. why? maybe accroding to class initialized */
struct kv_t {
	std::string key;
	std::string value;
	unsigned rev;
};
struct op_t {
	enum op_type_t : unsigned { kPut = 0, kDel = 1 } op;
	kv_t kv;
	static op_t Put(std::string const& key, std::string const& value,
			unsigned const rev) {
		 return op_t{.op = op_type_t::kPut,
		  .kv = kv_t{.key = key, .value = value, .rev = rev}};
	 }
};
class RedisMetaService : public std::enable_shared_from_this<RedisMetaService> {
public:
	/* redis 不能构造redis_ 改为引用*/
	RedisMetaService(std::unique_ptr<AsyncRedis>& redis, std::unique_ptr<AsyncRedis>& redis2) 
		: redis_(redis), sync_redis_(redis2), worker(meta_context_) {}
	void requestAll(function<void(std::vector<op_t> const&, unsigned)> callback);
	inline io_service& GetMetaContext() { return meta_context_; }
private:
	std::unique_ptr<AsyncRedis>& redis_;
	std::unique_ptr<AsyncRedis>& sync_redis_;
	io_service meta_context_;
	io_service::work worker;
	string prefix_ = "key";
};

void RedisMetaService::requestAll(function<void(std::vector<op_t> const&, unsigned)> callback) {
	auto self(shared_from_this());
	redis_->command<std::vector<std::string>>("keys", "*", 
      [self, callback](Future<std::vector<std::string>> &&resp) {
        auto const& vec = resp.get();
        std::vector<op_t> ops(vec.size());
        for(int i = 0; i < vec.size(); i++) {
          if (!boost::algorithm::starts_with(vec[i],
                                          self->prefix_)) {
            // ignore garbage values
            continue;
          }
          std::string op_key = boost::algorithm::erase_head_copy(
            vec[i], self->prefix_.size());
          auto op = op_t::Put(
            op_key, *(self->sync_redis_->get(vec[i]).get()), 0);
          ops.emplace_back(op);
        }
        self->GetMetaContext().post(
            boost::bind(callback, ops, stoi(*(self->sync_redis_->get("redis_revision").get()))));
    });	
}

void workThread(io_service& iosv) {
    iosv.run();
    cout << "End." << endl;
}

int main() {
    //auto iosv =std::make_shared<io_service>();
    // 等待新的任务加入
    //auto worker = std::make_shared<io_service::work>(*iosv);

    ConnectionOptions opts;
    opts.host = "192.168.127.130";
    opts.password = "root";
    opts.port = 6379;

    ConnectionPoolOptions pool_opts;
    pool_opts.size = 3;

	std::unique_ptr<AsyncRedis> redis_client;
	redis_client.reset(new AsyncRedis(opts, pool_opts));

    ConnectionOptions opts2;
    opts2.host = "192.168.127.130";
    opts2.password = "root";
    opts2.port = 6379;

    ConnectionPoolOptions pool_opts2;
    pool_opts2.size = 1;

    auto async_redis = AsyncRedis(opts2, pool_opts2);

    Future<std::string> ping_res = redis_client->ping();
    if(ping_res.get() == "PONG") {
        cout << "hello redis" << endl;
    }
	
	//std::unique_ptr<AsyncRedis> redis = make_shared<AsyncRedis>(async_redis);
	//std::unique_ptr<AsyncRedis> redis(new AsyncRedis(async_redis)); // 不行，会调用拷贝构造
	// error: conversion from ‘sw::redis::AsyncRedis*’ to non-scalar type ‘std::unique_ptr<sw::redis::AsyncRedis>’ requested
	//std::unique_ptr<AsyncRedis> redis = &async_redis; 
	std::unique_ptr<AsyncRedis> redis(&async_redis); 
	
	// 不能使用这种方式创建对象，否则会有terminate called after throwing an instance of 'std::bad_weak_ptr'   what():  bad_weak_ptr
	//RedisMetaService meta_service(redis);
	shared_ptr<RedisMetaService> redis_ptr = make_shared<RedisMetaService>(redis_client, redis);

	boost::thread_group threads;
    threads.create_thread(boost::bind(&workThread, ref(redis_ptr->GetMetaContext())));

	cout << "is_ok" << endl;

	redis_ptr->requestAll([](vector<op_t> const& ops, unsigned rev){
		for(auto const& item : ops) {
			cout << item.kv.key << " " << item.kv.value << endl;;
		}
		cout << "in callback rev: " << rev << endl;
	});


	cin.get();
	//meta_service.worker.stop();
	redis_ptr->GetMetaContext().stop();

	return 0;
}
