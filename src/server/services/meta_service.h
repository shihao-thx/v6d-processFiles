#ifndef SRC_SERVER_SERVICES_META_SERVICE_H_
#define SRC_SERVER_SERVICES_META_SERVICE_H_

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "boost/asio.hpp"
#include "boost/asio/steady_timer.hpp"
#include "boost/bind.hpp"
#include "boost/range/iterator_range.hpp"
#include "boost/optional/optional.hpp"

#include "common/util/callback.h"
#include "common/util/env.h"
#include "common/util/functions.h"
#include "common/util/json.h"
#include "common/util/status.h"
#include "server/server/vineyard_server.h"


namespace vineyard {

namespace asio = boost::asio;

class IMetaService : public std::enable_shared_from_this<IMetaService> {
public:
  struct kv_t {
    std::string key;
    std::string value;
    unsigned rev; 
  };

  struct op_t {
    enum op_type_t : unsigned { kPut = 0, kDel = 1 } op; // hao: the type of kPut and kPut are unsigned
    kv_t kv;
    std::string ToString() const {
      std::stringstream ss; 
      ss.str(""); // copy string "" to ss and return void   
      ss.clear(); // reset all the state of ss 
      ss << ((op == kPut) ? "put " : "del ");
      ss << "[" << kv.rev << "] " << kv.key << " -> " << kv.value;
      return ss.str(); // return all string copied in ss
    }

    static op_t Del(std::string const& key) {
      return op_t{.op = op_type_t::kDel,
                  .kv = kv_t{.key = key, .value = "", .rev = 0}};
    }
    static op_t Del(std::string const& key, unsigned const rev) {
      return op_t{.op = op_type_t::kDel,
                  .kv = kv_t{.key = key, .value = "", .rev = rev}};
    }
    // send to etcd
    template <typename T>
    static op_t Put(std::string const& key, T const& value) {
      return op_t{
          .op = op_type_t::kPut,
          .kv =
              kv_t{.key = key, .value = json_to_string(json(value)), .rev = 0}};
    }
    template <typename T>
    static op_t Put(std::string const& key, json const& value) {
      return op_t{
          .op = op_type_t::kPut,
          .kv = kv_t{.key = key, .value = json_to_string(value), .rev = 0}};
    }
    // receive from etcd
    static op_t Put(std::string const& key, std::string const& value,
                    unsigned const rev) {
      return op_t{.op = op_type_t::kPut,
                  .kv = kv_t{.key = key, .value = value, .rev = rev}};
    }
  };

  struct watcher_t {
    watcher_t(callback_t<const json&, const std::string&> w,
              const std::string& t)
        : watcher(w), tag(t) {}
    callback_t<const json&, const std::string&> watcher;
    std::string tag;
  };

  virtual ~IMetaService() { /*LOG(INFO) << "dtor the metadata service";*/ }
  explicit IMetaService(vs_ptr_t& server_ptr)
      : server_ptr_(server_ptr), rev_(0), meta_sync_lock_("/meta_sync_lock") {
    stopped_.store(false);
  }

  static std::shared_ptr<IMetaService> Get(vs_ptr_t);

private:
  std::atomic<bool> stopped_;
  json meta_;
  vs_ptr_t server_ptr_;

  unsigned rev_;
  bool backend_retrying_;

  std::string meta_sync_lock_;
};

}

#endif