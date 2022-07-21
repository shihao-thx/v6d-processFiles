#ifndef SRC_SERVER_SERVER_VINEYARD_RUNNER_H_
#define SRC_SERVER_SERVER_VINEYARD_RUNNER_H_

#include "boost/asio.hpp"
#include <atomic>
#include <vector>
#include <string>
#include "common/util/status.h"
#include "common/util/uuid.h"


namespace vineyard{

namespace asio=boost::asio;
using session_map_t = tbb::concurrent_hash_map<SessionID, vs_ptr_t>;

class VineyardServer;

class VineyardRunner : public std::enable_shared_from_this<VineyardRunner> {
public:
    static std::shared_ptr<VineyardRunner> Get(const json& spec);
    Status Serve();
    //Status Finalize();
    //Status GetRootSession(vs_ptr_t& vs_ptr);
    //Status CreateNewSession(std::string const& bulk_store_type,
                          callback_t<std::string const&> callback);
    //Status Delete(SessionID const& sid);
    //Status Get(SessionID const& sid, vs_ptr_t& session);
    //bool Exists(SessionID const& sid);
    //void Stop();
    bool Running() const;

private:
    // 必须由成员方法完成构造，Get(const json& spec)方法
    //explicit VineyardRunner(const json& spec);
    explicit VineyardRunner(const string& spec);
    std::string spec_template_;

    unsigned int concurrency_;

#if BOOST_VERSION >= 106600
    asio::io_context context_, meta_context_;
    using ctx_guard = asio::executor_work_guard<asio::io_context::executor_type>;
#else
    asio::io_service context_, meta_context_;
    using ctx_guard = std::unique_ptr<boost::asio::io_service::work>;
#endif

    ctx_guard guard_, meta_guard_;
    std::vector<std::thread> workers_;

    //session_map_t sessions_;
    std::atomic_bool stopped_;
};
    
}

#endif