#include "lib/logger.hpp"
#include "rslc.hpp"
#include <fstream>

int main(int argc, const char **argv) {
  rslc::Logger::init(rslc::LOG_VERBOSE, true, false);
  rslc::Logger::get() << rslc::Logger::ready(rslc::LOG_DEBUG, "MAIN")
                      << "Logger initialized" << rslc::Logger::endl;
  std::ifstream src(argv[1]);
  rslc::compiler c(src);
  auto strm = c.run_lexer();
  rslc::lexer::token tok = rslc::lexer::token_invalid(0);
  size_t line = 0;
  while (!std::holds_alternative<rslc::lexer::token_eof>(tok)) {
    strm >> tok;
    std::visit(
        [&line](auto &var) {
          if (var.lineno() > line) {
            std::cout << std::endl;
            line++;
          }
        },
        tok);
    std::cout << tok << " ";
  }
  std::cout << std::endl;

  rslc::Logger::get() << rslc::Logger::ready(rslc::LOG_DEBUG, "MAIN")
                      << "Compiler Finished" << rslc::Logger::endl;

  return 0;
}
