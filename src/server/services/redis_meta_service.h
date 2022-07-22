#ifndef SRC_SERVER_SERVICES_REDIS_META_SERVICE_H_
#define SRC_SERVER_SERVICES_REDIS_META_SERVICE_H_

#include "server/services/meta_service.h"

namespace vineyard {

class RedisMetaService : public IMetaService {
public:
    inline void Stop() override;

    ~RedisMetaService() override {}
protected:
    explicit RedisMetaService(vs_ptr_t& server_ptr) : IMetaService(server_ptr),
            etcd_spec_(server_ptr_->GetSpec()["metastore_spec"]),
        prefix_(etcd_spec_["etcd_prefix"].get<std::string>() + "/" +
                SessionIDToString(server_ptr->session_id())) {
    handled_rev_.store(0);
  }

    const json etcd_spec_;
    const std::string prefix_;
private:
    std::atomic<unsigned> handled_rev_;
};
}

#endif