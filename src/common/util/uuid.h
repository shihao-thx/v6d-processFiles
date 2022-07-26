#ifndef SRC_COMMON_UTIL_UUID_H_
#define SRC_COMMON_UTIL_UUID_H_

#include <string>

namespace vineyard {
    using ObjectID = uint64_t;
    using Signature = uint64_t;
    using InstanceID = uint64_t;
    using SessionID = int64_t;
    
    constexpr inline SessionID RootSessionID() { return 0x0000000000000000UL; }
}
#endif