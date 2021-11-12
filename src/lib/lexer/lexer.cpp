#include <cctype>
#include <sstream>

#include "lib/lexer/lexer.hpp"

using namespace rslc::lexer;

token token_stream::extract() {
  std::stringstream buffer;

  if (src.eof())
    return token_eof(line);

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

  if (curr == ':')
    return token_colon(line);
  if (curr == ',')
    return token_comma(line);
  if (curr == '(' || curr == ')')
    return token_bracket(curr, line);

  while (!src.eof() &&
         ((curr >= 'A' && curr <= 'Z') || (curr >= 'a' && curr <= 'z') ||
          (curr >= '0' && curr <= '9') || curr == '.' ||
          token_operator::is_op_char(curr))) {
    buffer << curr;
    curr = src.get();
  }

  if (!src.eof()) {
    src.putback(curr);
  }

  std::string res = buffer.str();
  if (res.length() == 0)
    return token_invalid(line);

  if (token_operator::is_operator(res)) {
    return token_operator(res, line);
  }

  std::cmatch m;
  if (std::regex_match(res.c_str(), m, token_literal::regex_int)) {
    return token_literal(std::strtol(res.c_str(), nullptr, 10), line);
  }
  if (std::regex_match(res.c_str(), m, token_literal::regex_flt)) {
    return token_literal(static_cast<float>(std::strtod(res.c_str(), nullptr)),
                         line);
  }
  if (res[0] == '@') {
    return token_directive(res, line);
  }
  return token_text(res, line);
}
