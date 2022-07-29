#include <redis++/async_redis++.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <iterator>
#include <unordered_map>
#include <unordered_map>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include<ctime>

using namespace sw::redis;
using namespace std;

void callback1(AsyncRedis& async_redis) {	
	async_redis.command<std::vector<std::string>>("keys", "*", 
		[](Future<vector<string>> &&fut){
		//	iosv->post(boost::bind(&watch, ref(async_redis), msg));
			sleep(10);
			for(auto const& item : fut.get()) {
       			 cout << item << " ";
   			 }
    		cout << endl;
		});
}

void callback2(AsyncRedis& async_redis) {	
	auto resp = async_redis.command<std::vector<std::string>>("keys", "*"); 
	for(auto const& item : resp.get()) 
		cout << item << " ";
	cout << endl;
	sleep(10);
}

void callback3(AsyncRedis& async_redis) {
	vector<string> keys = { "key43", "key75", "key61", "key28" };
//	for(auto const& item : keys) cout << item << " ";
	/*async_redis.command<std::vector<OptionalString>>("mget", keys.begin(), keys.end(),
            [](Future<std::vector<std::string>> &&resp) {
              for(auto const& item : resp.get())
			  	cout << item << endl;
              });*/
	 async_redis.command<std::vector<std::string>>("mget", keys.begin(), keys.end(),
              [](Future<std::vector<std::string>> &&resp) {
                for(auto const& item : resp.get())
                  cout << item << endl;
                });
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
    pool_opts.size = 1;
    auto async_redis = AsyncRedis(opts, pool_opts);

    Future<std::string> ping_res = async_redis.ping();
    if(ping_res.get() == "PONG") {
        cout << "hello redis" << endl;
    }

	/*
	long n=0;
	clock_t start,finish;
	
	start=clock();
	callback1(async_redis);
	finish=clock();
    cout<< "callback1 consume: " << (finish-start)/CLOCKS_PER_SEC << endl;
	*/

	//cin.get();
	//auto const& vec = resp.get();

	//for(auto const& item : vec) {
	//	cout << item << " ";
	//}
	//cout << endl;
	//start=clock();
    //callback2(async_redis);
    //finish=clock();
    //cout<< "callback2 consume: " << (finish-start)/CLOCKS_PER_SEC << endl;

	callback3(async_redis);

 	cin.get();

	return 0;
}
