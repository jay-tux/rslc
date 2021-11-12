#ifndef _RSLC_LIB_LOGGER
#define _RSLC_LIB_LOGGER

#include <iostream>

namespace rslc {
enum LogLevel { LOG_VERBOSE, LOG_NORMAL, LOG_QUIET };
enum LogType { LOG_DEBUG, LOG_MESG, LOG_WARN, LOG_ERR };
class Logger {
public:
  struct endl_t {};
  struct ready_t {
    LogType lvl;
    std::string src;
  };
  static endl_t endl;
  static Logger &init(LogLevel lvl, bool on_stderr, bool color);
  static bool is_init();
  static Logger &get();
  inline static ready_t ready(LogType t, std::string src) { return {t, src}; }

  template <typename T> friend Logger &operator<<(Logger &l, const T other) {
    l.strm << other;
    return l;
  }

private:
  inline Logger(LogLevel lvl, std::ostream &strm, bool color)
      : lvl{lvl}, curr{LOG_DEBUG}, strm{strm}, color{color} {}
  LogLevel lvl;
  LogType curr;
  std::ostream &strm;
  bool color;
};
} // namespace rslc

inline std::ostream &operator<<(std::ostream &target,
                                const rslc::Logger::endl_t) {
  return target << std::endl;
}

inline std::ostream &operator<<(std::ostream &target,
                                const rslc::LogType type) {
  switch (type) {
  case rslc::LOG_DEBUG:
    return target << " DEBUG ";
  case rslc::LOG_MESG:
    return target << "MESSAGE";
  case rslc::LOG_WARN:
    return target << "WARNING";
  case rslc::LOG_ERR:
    return target << " ERROR ";
  }
  return target;
}

inline std::ostream &operator<<(std::ostream &target,
                                const rslc::Logger::ready_t r) {
  return target << std::endl << "[" << r.lvl << " in " << r.src << "]: ";
}

#endif // _RSLC_LIB_LOGGER
