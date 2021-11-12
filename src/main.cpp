#include "lib/logger.hpp"
#include "rslc.hpp"
#include <fstream>

int main(int argc, const char **argv) {
  rslc::Logger::init(rslc::LOG_VERBOSE, true, false);
  rslc::Logger::get() << rslc::Logger::ready(rslc::LOG_DEBUG, "MAIN")
                      << "Logger initialized";
  std::ifstream src(argv[1]);
  rslc::compiler c(src);
  auto strm = c.run_lexer();
  auto ast = std::move(c.run_syntax_analysis(strm));

  rslc::Logger::get() << rslc::Logger::ready(rslc::LOG_DEBUG, "MAIN")
                      << "Compiler Finished" << rslc::Logger::endl;

  return 0;
}
