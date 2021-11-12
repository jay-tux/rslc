#ifndef _RSLC_SYNTAX_TREE
#define _RSLC_SYNTAX_TREE

#include "../lexer/token.hpp"
#include <vector>

namespace rslc {
namespace syntax {
struct node {
  using child_cont = std::vector<node>;
  inline node(node *parent, lexer::token value)
      : parent{parent}, value{value}, children{child_cont()} {}
  node *parent;
  lexer::token value;
  child_cont children;
};
} // namespace syntax
} // namespace rslc

#endif // _RSLC_SYNTAX_TREE
