#include <cctype>
#include <sstream>

#include "lib/lexer/lexer.hpp"

using namespace rslc::lexer;

token token_stream::extract() {
  std::stringstream buffer;

  char curr = src.get();
  while (std::isspace(curr) && !src.eof()) {
    if (curr == '\n')
      line++;
    curr = src.get();
  }

  if (src.eof())
    return token_eof(line);

  if (curr == '{' || curr == '}')
    return token_brace(curr, line);
  return token_invalid(line);
}
