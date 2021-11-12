#include "../inc/rslc.hpp"
#include <fstream>

int main(int argc, const char **argv) {
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

  return 0;
}
