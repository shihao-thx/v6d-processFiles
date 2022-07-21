#ifndef SRC_COMMON_UTIL_STATUS_H_
#define SRC_COMMON_UTIL_STATUS_H_

#include <string>

namespace vineyard {

enum class StatusCode : unsigned char {
  kOK = 0,
  kInvalid = 1,
  kKeyError = 2,
  kTypeError = 3,
  kIOError = 4,
  kEndOfFile = 5,
  kNotImplemented = 6,
  kAssertionFailed = 7,
  kUserInputError = 8,

  kObjectExists = 11,
  kObjectNotExists = 12,
  kObjectSealed = 13,
  kObjectNotSealed = 14,
  kObjectIsBlob = 15,

  kMetaTreeInvalid = 21,
  kMetaTreeTypeInvalid = 22,
  kMetaTreeTypeNotExists = 23,
  kMetaTreeNameInvalid = 24,
  kMetaTreeNameNotExists = 25,
  kMetaTreeLinkInvalid = 26,
  kMetaTreeSubtreeNotExists = 27,

  kVineyardServerNotReady = 31,
  kArrowError = 32,
  kConnectionFailed = 33,
  kConnectionError = 34,
  kEtcdError = 35,
  kAlreadyStopped = 36,

  kNotEnoughMemory = 41,
  kStreamDrained = 42,
  kStreamFailed = 43,
  kInvalidStreamState = 44,
  kStreamOpened = 45,

  kGlobalObjectInvalid = 51,

  kUnknownError = 255
};

class Status {
public:
  Status() noexcept : state_(nullptr) {} //noexcept: don't throw exception //form shihao
  ~Status() noexcept {
    if (state_ != nullptr) {
      DeleteState();
    }
  }
  /// Return a success status
  inline static Status OK() { return Status(); }
private:
    struct State {
        StatusCode code;
        std::string msg;
    };
    State* state_;

    void DeleteState() {
        delete state_;
        state_ = nullptr;
    }
};

#endif
}