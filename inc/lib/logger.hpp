#ifndef _RSLC_LIB_LOGGER
#define _RSLC_LIB_LOGGER

#include <iostream>

namespace rslc {
enum LogLevel { LOG_VERBOSE, LOG_NORMAL, LOG_QUIET };
enum LogType { LOG_DEBUG, LOG_MESG, LOG_WARN, LOG_ERR };
class Logger {
public:
  struct endl_t {};
  static endl_t endl;
  static Logger &init(LogLevel lvl, bool on_stderr, bool color);
  static bool is_init();
  static Logger &get(LogType l, std::string src);
  static Logger &cntLog();

  template <typename T> friend Logger &operator<<(Logger &l, const T other) {
    l.strm << other;
    return l;
  }

private:
  inline Logger(LogLevel lvl, std::ostream &strm, bool color)
      : lvl{lvl}, strm{strm}, color{color} {}
  LogLevel lvl;
  std::ostream &strm;
  bool color;
};
} // namespace rslc

inline std::ostream &operator<<(std::ostream &target, const rslc::Logger::endl_t e) {
  return target << std::endl;
}

#endif // _RSLC_LIB_LOGGER
