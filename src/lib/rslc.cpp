#include "../../inc/rslc.hpp"

using namespace rslc;
using namespace rslc::lexer;
using namespace rslc::syntax;
using namespace rslc::codegen;

template <typename LT, typename... Args> LT &lazy_init(Args... args) {
  static LT res(args...);
  return res;
}

token_stream &compiler::run_lexer() const {
  token_stream &res = lazy_init<token_stream>();
  // do lexer stuff
  return res;
}

ast &compiler::run_syntax_analysis(lexer::token_stream &stream) const {
  ast &res = lazy_init<ast>();
  // do syntax stuff
  return res;
}

codestream &compiler::run_code_generator(syntax::ast &ast) const {
  codestream &res = lazy_init<codestream>();
  // do code generation stuff
  return res;
}
