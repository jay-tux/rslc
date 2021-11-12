#ifndef _RSLC_SYNTAX_SYNTAX
#define _RSLC_SYNTAX_SYNTAX

#include "../lexer/lexer.hpp"
#include "../lexer/token.hpp"
#include "tree.hpp"
#include <memory>
#include <optional>

namespace rslc {
namespace syntax {
class ast {
public:
  inline ast() : root{nullptr}, at{nullptr} {}
  void add_node(lexer::token t);
  inline void to_parent() {
    if (at == nullptr || at->parent == nullptr)
      return;
    at = at->parent;
  }

  void from_lexer(lexer::token_stream &strm);

private:
  std::unique_ptr<node> root;
  node *at;
}; // ast
} // namespace syntax
} // namespace rslc

#endif // _RSLC_SYNTAX_SYNTAX
