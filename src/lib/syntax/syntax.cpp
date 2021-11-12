#include "lib/syntax/syntax.hpp"
#include "lib/logger.hpp"

using namespace rslc;
using namespace rslc::syntax;

void ast::from_lexer(lexer::token_stream &strm) {
  Logger &l = Logger::get();
  l << Logger::ready(LOG_DEBUG, "AST CTR") << "Starting construction of AST";
  lexer::token t = lexer::token_invalid(0);
  //
  l << Logger::ready(LOG_DEBUG, "AST CTR") << "AST Constructed";
}
