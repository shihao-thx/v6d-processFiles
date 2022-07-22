#include "common/util/uuid.h"

#include <cstdio>
#include <cstdlib>

namespace vineyard {

const std::string SessionIDToString(const SessionID id) {
  thread_local char buffer[18] = {'\0'};
  std::snprintf(buffer, sizeof(buffer), "S%016" PRIx64, id);
  return std::string(buffer);
}

}
