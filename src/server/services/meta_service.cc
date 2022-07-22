#include "server/services/meta_service.h"

#include <algorithm>
#include <memory>


namespace vineyard {

std::shared_ptr<IMetaService> IMetaService::Get(vs_ptr_t server_ptr) {
  std::string meta = "redis";
  if (meta == "redis") {
    return std::shared_ptr<IMetaService>(new RedisMetaService(server_ptr));
  }
  return nullptr;
}

}