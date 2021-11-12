#include "../inc/rslc.hpp"
#include <fstream>

int main(int argc, const char **argv) {
  std::ifstream src(argv[1]);
  rslc::compiler c(src);
  auto strm = c.run_lexer();

  size_t line = 0;
  strm.visit_all([&line](auto &t, auto &tok) {
    // auto var = std::get<decltype(t)>(t);
    if (t.lineno() > line) {
      std::cout << std::endl;
      line++;
    }
    std::cout << tok << " ";
  });

  std::cout << std::endl;
  return 0;
}
