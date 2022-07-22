#include "server/server/vineyard_runner.h"
#include "server/server/vineyard_server.h"

#include "boost/bind.hpp"

#include "common/util/status.h"


namespace vineyard {

VineyardRunner::VineyardRunner(const std::string& spec)
    : spec_template_(spec),
      concurrency_(std::thread::hardware_concurrency()),
      context_(concurrency_),
      meta_context_(),
#if BOOST_VERSION >= 106600
      guard_(asio::make_work_guard(context_)),
      meta_guard_(asio::make_work_guard(meta_context_))
#else
      guard_(new boost::asio::io_service::work(context_)),
      meta_guard_(new boost::asio::io_service::work(context_))
#endif
{
}
// 获得自身的指针
std::shared_ptr<VineyardRunner> VineyardRunner::Get(const std::string& spec) {
    return std::shared_ptr<VineyardRunner>(new VineyardRunner(spec));
}

bool VineyardRunner::Running() const { return !stopped_.load(); }

Status VineyardRunner::Serve() {
  stopped_.store(false);

  //VINEYARD_ASSERT(sessions_.empty(), "Vineyard Runner already started"); // sessions_.empty()为假，输出"Vineyard Runner already started"
  auto root_vs = std::make_shared<VineyardServer>( 
      spec_template_, RootSessionID(), shared_from_this(), context_,
      meta_context_, [](Status const& s, std::string const&) { return s; });
  //sessions_.emplace(RootSessionID(), root_vs);

  // start a root session
  VINEYARD_CHECK_OK(root_vs->Serve("Normal"));
  // 新建线程
  for (unsigned int idx = 0; idx < concurrency_; ++idx) {
#if BOOST_VERSION >= 106600
    workers_.emplace_back(
        boost::bind(&boost::asio::io_context::run, &context_));
#else
    workers_.emplace_back(
        boost::bind(&boost::asio::io_service::run, &context_));
#endif
  }

  meta_context_.run(); // 阻塞
  return Status::OK();
}

}