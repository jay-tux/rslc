#include "lib/logger.hpp"
#include <stdexcept>

using namespace rslc;

static Logger *_inst = nullptr;

const char *type_str(LogType l) {
  switch (l) {
  case rslc::LOG_DEBUG:
    return " DEBUG ";
  case rslc::LOG_MESG:
    return "MESSAGE";
  case rslc::LOG_WARN:
    return "WARNING";
  case rslc::LOG_ERR:
    return " ERROR ";
  }
}

Logger &Logger::init(LogLevel lvl, bool on_stderr, bool color) {
  if (_inst != nullptr)
    delete _inst;
  _inst = new Logger(lvl, on_stderr ? std::cerr : std::cout, color);
  return *_inst;
}

bool Logger::is_init() { return _inst != nullptr; }

Logger &Logger::get(LogType l, std::string src) {
  if (!is_init())
    throw std::logic_error("Logger not yet initialized.");

  _inst->strm << std::endl;
  return *_inst << "[" << type_str(l) << " in " << src << "]: ";
}

Logger &Logger::cntLog() {
  if (!is_init())
    throw std::logic_error("Logger not yet initialized.");
  return *_inst;
}
