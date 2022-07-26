#include <redis++/async_redis++.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <iterator>
#include <unordered_map>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

using namespace sw::redis;
using namespace std;
using namespace boost::asio;

unsigned rev_ = 0;

void workThread(shared_ptr<io_service> iosv) {
	iosv->run();
	cout << "End." << endl;
}
void watch(AsyncRedis& async_redis, string rev) {
	cout << "in watch " << "rev: " << rev << endl;
	//vector<string> keys;
	auto resp = async_redis.lrange<std::vector<std::string>>("optlist", rev_, -1);
	vector<string> puts;
	vector<string> dels;
	for(auto const& item : resp.get()) {
		auto hresp = async_redis.hgetall<vector<string>>(item);
		auto const& vec = hresp.get();
		//auto len = hresp.get().size() << 1;
		int j;
		for (int i=0; i<(vec.size() >> 1); i++){
			j = i << 1;
			if(vec[j+1] == "0") {
				// keys need to Put
				puts.emplace_back(vec[j]);
			} else if(vec[j+1] == "1") {
				// keys need to Del
				dels.emplace_back(vec[j]);
			}
		}
	}

	cout << "the keys to put:" << endl;
	for(auto const& item : puts) {
		cout << item << " ";
	}
	cout << endl;
	cout << "the keys to del:" << endl;
	for(auto const& item : dels) {
		cout << item << " ";
	}
	cout << endl;

	rev_ = stoi(rev); // 下次从下一个获取 
	cout << "rev: " << rev_ << endl;
}

int main() {
	auto iosv =std::make_shared<io_service>();
	// 等待新的任务加入
	auto worker = std::make_shared<io_service::work>(*iosv);

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

	AsyncSubscriber sub = async_redis.subscriber();

	sub.on_message([iosv, &async_redis](std::string channel, std::string msg) {
     // Process message of MESSAGE type.
	 	iosv->post(boost::bind(&watch, ref(async_redis), msg));
     });

	sub.subscribe("channel");

	boost::thread_group threads;
    threads.create_thread(boost::bind(&workThread, iosv));

	/*
    for (auto item : kvs) {
        printf("key :%d, value:%d\n", item.first, item.second);
    }*/
	// 有work的时候，run会阻塞，所以一般将run()的调用放在工作线程，而不是主线程
	// 因为是实验，所以为了能够实现按任意键退出程序，所有需要工作线程
	//iosv->run();
	cin.get();
	worker.reset();
	//threads.join_all();

    return 0;
}

