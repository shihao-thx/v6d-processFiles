#include "boost/asio.hpp"


namespace vineyard{
    namespace asio=boost::asio;
    using session_map_t = tbb::concurrent_hash_map<SessionID, vs_ptr_t>;
    
}