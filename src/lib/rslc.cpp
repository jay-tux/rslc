#include "rslc.hpp"

using namespace rslc;
using namespace rslc::lexer;
using namespace rslc::syntax;
using namespace rslc::codegen;

template <typename LT, typename... Args> LT &lazy_init(Args... args) {
  static LT res(args...);
  return res;
}

token_stream &compiler::run_lexer() const {
  // prepare arguments; from flags & args
  token_stream &res = lazy_init<token_stream, std::istream &>(this->source);
  return res;
}

ast &compiler::run_syntax_analysis(lexer::token_stream &stream) const {
  // prepare arguments; from flags & args
  ast &res = lazy_init<ast>();
  res.from_lexer(stream);
  return res;
}

codestream &compiler::run_code_generator(syntax::ast &ast) const {
  // prepare arguments; from flags & args
  codestream &res = lazy_init<codestream>();
  return res;
}
