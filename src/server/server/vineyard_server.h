#ifndef SRC_SERVER_SERVER_VINEYARD_SERVER_H_
#define SRC_SERVER_SERVER_VINEYARD_SERVER_H_

#include <set>
#include <string>
#include <thread>
#include <vector>

#include "boost/asio.hpp"

#include "common/util/uuid.h"
#include "common/util/callback.h"
#include "common/util/status.h"
#include "common/util/json.h"
#include "common/util/status.h"

#include "server/server/vineyard_runner.h"

namespace vineyard {

namespace asio = boost::asio;
class IMetaService;

/**
 * @brief DeferredReq aims to defer a socket request such that the request
 * is executed only when the metadata satisfies some specific condition.
 *
 */
class DeferredReq {
 public:
  using alive_t = std::function<bool()>;
  using test_t = std::function<bool(const json& meta)>;
  using call_t = std::function<Status(const json& meta)>;

  DeferredReq(alive_t alive_fn, test_t test_fn, call_t call_fn)
      : alive_fn_(alive_fn), test_fn_(test_fn), call_fn_(call_fn) {}

  bool Alive() const;

  bool TestThenCall(const json& meta) const;

 private:
  alive_t alive_fn_;
  test_t test_fn_;
  call_t call_fn_;
};

class VineyardServer : public std::enable_shared_from_this<VineyardServer> {
 public:
  explicit VineyardServer(const std::string& spec, const SessionID& session_id,
                          std::shared_ptr<VineyardRunner> runner,
#if BOOST_VERSION >= 106600
                          asio::io_context& context,
                          asio::io_context& meta_context,
#else
                          asio::io_service& context,
                          asio::io_service& meta_context,
#endif
                          callback_t<std::string const&> callback);
  Status Serve(std::string const& bulk_store_type);
  //Status Finalize();
  //inline const json& GetSpec() { return spec_; }
  //inline const std::string GetDeployment() {
  //  return spec_["deployment"].get_ref<std::string const&>();
  //} 

#if BOOST_VERSION >= 106600
  inline asio::io_context& GetContext() { return context_; }
  inline asio::io_context& GetMetaContext() { return meta_context_; }
#else
  inline asio::io_service& GetContext() { return context_; }
  inline asio::io_service& GetMetaContext() { return meta_context_; }
#endif
  inline std::string GetBulkStoreType() { return bulk_store_type_; }

  template <typename T = ObjectID>
  auto GetBulkStore() {
    return static_if<std::is_same<T, ObjectID>{}>(  // 使用默认ObjectID类型，则返回bulk_store_
        [this]() { return bulk_store_; },
        [this]() { return plasma_bulk_store_; })(); 
  }

  //inline std::shared_ptr<StreamStore> GetStreamStore() { return stream_store_; }
  inline std::shared_ptr<VineyardRunner> GetRunner() { return runner_; }

  //void MetaReady();
  //void BulkReady();
  //void IPCReady();
  //void RPCReady();
  //void BackendReady();
  //void Ready();

  Status GetData(const std::vector<ObjectID>& ids, const bool sync_remote,
                 const bool wait,
                 DeferredReq::alive_t alive,  // if connection is still alive
                 callback_t<const json&> callback);

  Status ListData(std::string const& pattern, bool const regex,
                  size_t const limit, callback_t<const json&> callback);

  Status ListAllData(callback_t<std::vector<ObjectID> const&> callback);

  Status CreateData(
      const json& tree,
      callback_t<const ObjectID, const Signature, const InstanceID> callback);

  Status Persist(const ObjectID id, callback_t<> callback);

  Status IfPersist(const ObjectID id, callback_t<const bool> callback);

  Status Exists(const ObjectID id, callback_t<const bool> callback);

  Status ShallowCopy(const ObjectID id, json const& extra_metadata,
                     callback_t<const ObjectID> callback);

  Status DeepCopy(const ObjectID id, const std::string& peer,
                  const std::string& peer_rpc_endpoint,
                  callback_t<const ObjectID&> callback);

  Status DelData(const std::vector<ObjectID>& id, const bool force,
                 const bool deep, const bool fastpath, callback_t<> callback);

  Status DeleteBlobBatch(const std::set<ObjectID>& blobs);

  Status DeleteAllAt(const json& meta, InstanceID const instance_id);

  Status PutName(const ObjectID object_id, const std::string& name,
                 callback_t<> callback);

  Status GetName(const std::string& name, const bool wait,
                 DeferredReq::alive_t alive,  // if connection is still alive
                 callback_t<const ObjectID&> callback);

  Status DropName(const std::string& name, callback_t<> callback);

  Status MigrateObject(const ObjectID object_id, const bool local,
                       const std::string& peer,
                       const std::string& peer_rpc_endpoint,
                       callback_t<const ObjectID&> callback);

  Status MigrateStream(const ObjectID object_id, const bool local,
                       const std::string& peer,
                       const std::string& peer_rpc_endpoint,
                       callback_t<const ObjectID&> callback);

  Status ClusterInfo(callback_t<const json&> callback);

  Status InstanceStatus(callback_t<const json&> callback);

  Status ProcessDeferred(const json& meta);

  inline SessionID session_id() const { return session_id_; }
  inline InstanceID instance_id() { return instance_id_; }
  inline std::string instance_name() { return instance_name_; }
  inline void set_instance_id(InstanceID id) {
    instance_id_ = id;
    instance_name_ = "i" + std::to_string(instance_id_);
  }

  inline std::string const& hostname() { return hostname_; }
  inline void set_hostname(std::string const& hostname) {
    hostname_ = hostname;
  }

  inline std::string const& nodename() { return nodename_; }
  inline void set_nodename(std::string const& nodename) {
    nodename_ = nodename;
  }

  const std::string IPCSocket();

  const std::string RPCEndpoint();

  void Stop();

  bool Running() const;

  ~VineyardServer();

 private:
  std::string spec_;
  SessionID session_id_;

#if BOOST_VERSION >= 106600
  asio::io_context& context_;
  asio::io_context& meta_context_;
#else
  asio::io_service& context_;
  asio::io_service& meta_context_;
#endif
  callback_t<std::string const&> callback_;

  std::shared_ptr<IMetaService> meta_service_ptr_;
  //std::unique_ptr<IPCServer> ipc_server_ptr_;
  //std::unique_ptr<RPCServer> rpc_server_ptr_;

  std::list<DeferredReq> deferred_;

  std::string bulk_store_type_;
  //std::shared_ptr<BulkStore> bulk_store_;
  //std::shared_ptr<PlasmaBulkStore> plasma_bulk_store_;
  //std::shared_ptr<StreamStore> stream_store_;
  std::shared_ptr<VineyardRunner> runner_;

  Status serve_status_;

  enum ready_t {
    kMeta = 0b1,
    kBulk = 0b10,
    kIPC = 0b100,
    kRPC = 0b1000,
    kBackendReady = 0b11,  // then we can serve ipc/rpc.
    kReady = 0b1111,
  };
  unsigned char ready_;
  std::atomic_bool stopped_;  // avoid invoke Stop() twice.

  InstanceID instance_id_;
  std::string instance_name_;
  std::string hostname_;
  std::string nodename_;
};

using vs_ptr_t = std::shared_ptr<VineyardServer>;

}

#endif