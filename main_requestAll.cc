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

/* free(): invalid pointer
Aborted (core dumped)
Why?
*/


/* cannot put in class. why? maybe accroding to class initialized No!!!*/
// 类中符号编译解释顺序需要好好回顾下
// 数据的实例化顺序一定是先于函数的，类中的类先初始化？
/*struct kv_t {
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
};*/
class RedisMetaService : public std::enable_shared_from_this<RedisMetaService> {
public:
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
	/* redis 不能构造redis_ 改为引用*/
	RedisMetaService(std::unique_ptr<AsyncRedis>& redis) 
		: redis_(redis), worker(meta_context_) {}
	void requestAll(function<void(std::vector<op_t> const&, unsigned)> callback);
	inline io_service& GetMetaContext() { return meta_context_; }
private:
	std::unique_ptr<AsyncRedis>& redis_;
//	std::unique_ptr<AsyncRedis>& sync_redis_;
	io_service meta_context_;
	io_service::work worker;
	string prefix_ = "key";
};

void RedisMetaService::requestAll(function<void(std::vector<op_t> const&, unsigned)> callback) {
	auto self(shared_from_this());
	redis_->command<std::vector<std::string>>("keys", "*", 
      [self, callback](Future<std::vector<std::string>> &&resp) {
        auto const& vec = resp.get();
        std::vector<std::string> keys;
		keys.emplace_back("mget");
		cout << vec.size() << endl; // 223
        for(int i = 0; i <vec.size(); i++) {
          if (!boost::algorithm::starts_with(vec[i],
                                          self->prefix_)) {
            // ignore garbage values
            continue;
          }
          keys.emplace_back(vec[i]);
		}
		/*for(auto const& item : keys) {
			cout << item << " ";
		}*/
		self->redis_->command<std::vector<std::string>>(keys.begin(), keys.end(),
		  [self, keys, callback](Future<std::vector<std::string>> &&resp) {
			auto const& vals = resp.get(); 
			std::string op_key;
			std::vector<op_t> ops(vals.size());
			// collect kvs
			for(int i=1; i<keys.size(); i++) {
                op_key = boost::algorithm::erase_head_copy(
                keys[i], self->prefix_.size());
			    ops.emplace_back(RedisMetaService::op_t::Put(
              	  op_key, vals[i-1], 0));
		    }
			cout << "can you see me 2" << endl;
		    self->redis_->get("redis_revision", 
		      [self, ops, callback](Future<OptionalString> &&resp) {
			    auto val = resp.get();
           		 self->GetMetaContext().post(
              		boost::bind(callback, ops, stoi(*val)));
	         });
		 });
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
/*
    ConnectionOptions opts2;
    opts2.host = "192.168.127.130";
    opts2.password = "root";
    opts2.port = 6379;

    ConnectionPoolOptions pool_opts2;
    pool_opts2.size = 3;

    auto async_redis = AsyncRedis(opts2, pool_opts2);
*/
    Future<std::string> ping_res = redis_client->ping();
    if(ping_res.get() == "PONG") {
        cout << "hello redis" << endl;
    }
	
	//std::unique_ptr<AsyncRedis> redis = make_shared<AsyncRedis>(async_redis);
	//std::unique_ptr<AsyncRedis> redis(new AsyncRedis(async_redis)); // 不行，会调用拷贝构造
	// error: conversion from ‘sw::redis::AsyncRedis*’ to non-scalar type ‘std::unique_ptr<sw::redis::AsyncRedis>’ requested
	//std::unique_ptr<AsyncRedis> redis = &async_redis; 
	//std::unique_ptr<AsyncRedis> redis(&async_redis); 
	
	// 不能使用这种方式创建对象，否则会有terminate called after throwing an instance of 'std::bad_weak_ptr'   what():  bad_weak_ptr
	//RedisMetaService meta_service(redis);
	shared_ptr<RedisMetaService> redis_ptr = make_shared<RedisMetaService>(redis_client);

	boost::thread_group threads;
    threads.create_thread(boost::bind(&workThread, ref(redis_ptr->GetMetaContext())));

	cout << "is_ok" << endl;

	redis_ptr->requestAll([](vector<RedisMetaService::op_t> const& ops, unsigned rev){
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
