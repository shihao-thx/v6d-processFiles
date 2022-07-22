#include "server/server/vineyard_server.h"

namespace vineyard {

bool DeferredReq::Alive() const { return alive_fn_(); }

bool DeferredReq::TestThenCall(const json& meta) const {
  if (test_fn_(meta)) {
    //VINEYARD_SUPPRESS(call_fn_(meta));
    return true;
  }
  return false;
}

VineyardServer::VineyardServer(const std::string& spec, const SessionID& session_id,
                               std::shared_ptr<VineyardRunner> runner,
#if BOOST_VERSION >= 106600
                               asio::io_context& context,
                               asio::io_context& meta_context,
#else
                               asio::io_service& context,
                               asio::io_service& meta_context,
#endif
                               callback_t<std::string const&> callback)
    : spec_(spec),
      session_id_(session_id),
      context_(context),
      meta_context_(meta_context),
      callback_(callback),
      runner_(runner),
      ready_(0) {
}

Status VineyardServer::Serve(std::string const& bulk_store_type) {
  stopped_.store(false);
  //this->bulk_store_type_ = bulk_store_type; // Normal
  bulk_store_type_ = bulk_store_type;

  meta_service_ptr_ = IMetaService::Get(shared_from_this()); // 派生类指针赋值给基类
  RETURN_ON_ERROR(this->meta_service_ptr_->Start());

  serve_status_ = Status::OK();
  return serve_status_;
}

}