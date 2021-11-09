#ifndef _RSLC_INT_ENUMS
#define _RSLC_INT_ENUMS

namespace rslc {
typedef enum rslc_flag { FLAG_NONE = 0 } rslc_flag;

inline rslc_flag join_flags(const rslc_flag one, const rslc_flag other) {
  return static_cast<rslc_flag>(static_cast<unsigned long>(one) |
                                static_cast<unsigned long>(other));
}

typedef enum rslc_arg { MAX_ARGS = 1 } rslc_arg;
} // namespace rslc

#endif //_RSLC_INT_ENUMS
