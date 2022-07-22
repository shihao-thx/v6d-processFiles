#ifndef SRC_COMMON_UTIL_CALLBACK_H_
#define SRC_COMMON_UTIL_CALLBACK_H_

#include <functional>

#include "common/util/status.h"

namespace vineyard {

template <class ...Args>
using callback_t = std::function<Status(const Status&, Args...)>; 

}
#endif