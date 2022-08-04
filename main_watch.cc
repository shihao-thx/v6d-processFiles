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
#include <boost/algorithm/string.hpp>

using namespace sw::redis;
using namespace std;
using namespace boost::asio;

unsigned rev_ = 0;

void workThread(shared_ptr<io_service> iosv) {
	iosv->run();
	cout << "End." << endl;
}

class RedisWatchHandler {
public:
	void operator()(std::unique_ptr<AsyncRedis>& async_redis, string rev);
private:
};

void RedisWatchHandler::operator()(std::unique_ptr<AsyncRedis>& async_redis, string rev) {
	cout << "in watch " << "rev: " << rev << endl;
    //vector<string> keys; 
    auto resp = async_redis->lrange<std::vector<std::string>>("optlist", rev_, stoi(rev)); // "-1“不行，而是“pub-1”    vector<string> puts;
	vector<string> puts;
    vector<string> dels;
	cout << "can you see me 0" << endl;
    for(auto const& item : resp.get()) {
		cout << "can you see me" << endl;
        auto hresp = async_redis->hgetall<vector<string>>(item);
        auto const& vec = hresp.get();
        //auto len = hresp.get().size() << 1;
        int j;
		cout << "can you see me 2" << endl;
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
    rev_++;
}

class RedisMetaService : public std::enable_shared_from_this<RedisMetaService> {
public:
    /* redis 不能构造redis_ 改为引用*/
    RedisMetaService(std::unique_ptr<AsyncRedis>& redis, shared_ptr<io_service> meta) : redis_(redis) ,iosv_(meta) {}
    void startDaemonWatch();
private:
    std::unique_ptr<AsyncRedis>& redis_;
	std::shared_ptr<AsyncSubscriber> watcher_;
    std::shared_ptr<RedisWatchHandler> handler_;
	shared_ptr<io_service> iosv_;
};

void RedisMetaService::startDaemonWatch() {
	handler_.reset(new RedisWatchHandler());
	watcher_.reset(new AsyncSubscriber(redis_->subscriber()));
	auto self(shared_from_this());
    //auto handler=handler_;
	watcher_->on_message([self](std::string channel, std::string msg) {
    	//self->iosv_->post(boost::bind<void>(ref(*(self->handler_)), ref(self->redis_), msg));
		(*(self->handler_))(self->redis_, msg);
    });
    this->watcher_->subscribe("opts");
}

int main() {
	auto iosv =std::make_shared<io_service>();
	auto worker = std::make_shared<io_service::work>(*iosv);

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
    
    shared_ptr<RedisMetaService> redis_ptr = make_shared<RedisMetaService>(redis_client, iosv);

	boost::thread_group threads;
 	threads.create_thread(boost::bind(&workThread, iosv));

	redis_ptr->startDaemonWatch();

	cin.get();
	worker.reset();

	return 0;
}
