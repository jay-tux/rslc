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

  inline void add_node(lexer::token t) {
    if (this->at == nullptr)
      this->root = std::make_unique<node>(nullptr, t);
    else {
      this->at->children.emplace_back(nullptr, t);
      this->at = &*this->at->children.rbegin();
    }
  }

  inline void to_parent() {
    if (at == nullptr || at->parent == nullptr)
      return;
    at = at->parent;
  }

  void from_lexer(lexer::token_stream &strm);

private:
  std::unique_ptr<node> root;
  node *at; // nullable reference
};          // ast
} // namespace syntax
} // namespace rslc

#endif // _RSLC_SYNTAX_SYNTAX
