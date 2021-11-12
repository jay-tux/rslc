#include "lib/logger.hpp"
#include <stdexcept>

using namespace rslc;

static Logger *_inst = nullptr;

Logger &Logger::init(LogLevel lvl, bool on_stderr, bool color) {
  if (_inst != nullptr)
    delete _inst;
  _inst = new Logger(lvl, on_stderr ? std::cerr : std::cout, color);
  return *_inst;
}

bool Logger::is_init() { return _inst != nullptr; }

Logger &Logger::get() {
  if (!is_init())
    throw std::logic_error("Logger not yet initialized.");
  return *_inst;
}
