#ifndef _RSLC_LEXER_LEXER
#define _RSLC_LEXER_LEXER

#include <istream>

#include "token.hpp"

namespace rslc {
namespace lexer {
class token_stream {
public:
  inline token_stream(std::istream &src) : src{src}, line{0} {}
  inline bool is_empty() const { return src.eof(); }
  token extract();
  inline friend token_stream &operator>>(token_stream &strm, token &target) {
    target = strm.extract();
    return strm;
  }

private:
  std::istream &src;
  size_t line;
}; // token_stream
} // namespace lexer
} // namespace rslc

#endif // _RSLC_LEXER_LEXER
