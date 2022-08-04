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
	//vector<string> keys = {"mget", "key43", "key75", "key61", "key28" };
	vector<string> keys;
	keys.emplace_back(string("mget"));
	keys.emplace_back("key43");
	keys.emplace_back("key75");
	keys.emplace_back("key61");
	keys.emplace_back("key28");
	for(auto& item : keys) {
		cout << item << " ";
	}
	cout << keys.size() <<endl;
//	for(auto const& item : keys) cout << item << " ";
	/*async_redis.command<std::vector<OptionalString>>("mget", keys.begin(), keys.end(),
            [](Future<std::vector<std::string>> &&resp) {
              for(auto const& item : resp.get())
			  	cout << item << endl;
              });*/
	 async_redis.command<std::vector<std::string>>(keys.begin(), keys.end(),
              [](Future<std::vector<std::string>> &&resp) {
                for(auto const& item : resp.get())
                  cout << item << endl;
                });
}

struct ops {
	string key;
    string val;
    unsigned type;
};

void callback4(AsyncRedis& async_redis) {
	int j=0;
	string prefix_ = "vineyard/";
      // produce kvs
    vector<ops> changes;
	for(int i=j; i<j+10; i++) {
	  	ops op{.key="key_" + to_string(i), .val = "value_" + to_string(i), .type = i};
	  	changes.emplace_back(op);
         /*
         changes.emplace_back(ops{.key=1, .val=i+1});
         */
	}

	unordered_map<string, unsigned> opts;
	vector<string> ks;
	std::vector<string> kvs;
	kvs.emplace_back("MSET");
	for(auto& op : changes) {
         //kvs.insert({prefix_ + op.key, op.val});
		 kvs.emplace_back(prefix_ + op.key);
         kvs.emplace_back(op.val);
         opts.insert({op.key, 0}); // push
		 ks.emplace_back(prefix_ + op.key);
    }
	
	//kvs.emplace_hint(kvs.begin(), "mset", "");
	//kvs.insert({"mset", ""});
	/*async_redis.command<void>(kvs.begin(), kvs.end(),
	  [](Future<void> &&resp) {
	  	cout << "in callback" << endl;
	  });*/
	async_redis.del(ks.begin(), ks.end(),
      [&async_redis,&opts](Future<long long> &&resp) {
 		async_redis.hset("opt1", opts.begin(), opts.end(),
           [](Future<long long> &&resp) {
			 cout << "in hset callback." << endl;
		  });
      });

	  cin.get();
	  /*
	for (auto itr = kvs.begin(); itr != kvs.end(); itr++)
        cout << itr->first << "\t"
             << itr->second << endl;*/
}

/*void callback4(AsyncRedis& async_redis) {
	
}*/
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

	//callback3(async_redis);
	callback4(async_redis);
	//callback5(async_redis);
 	cin.get();

	return 0;
}
