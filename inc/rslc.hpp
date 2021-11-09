#ifndef _RSLC_RSLC
#define _RSLC_RSLC

#include <istream>
#include <memory> // as long as my ccls keeps failing on optional
#include <queue>
#include <string>
#include <vector>

#include "int/codegen/generator.hpp"
#include "int/enums.hpp"
#include "int/error.hpp"
#include "int/lexer/lexer.hpp"
#include "int/syntax/syntax.hpp"

#include "int/data/defaults.hpp"

/*!
 *  RSLC main namespace.
 */
namespace rslc {
class compiler {
public:
  using err_queue_t = std::queue<rslc_error>;

  inline compiler(std::istream &source)
      : errors{err_queue_t()}, flags{COMPILER_DEFAULT_FLAGS},
        args{COMPILER_DEFAULT_ARGS}, source{source} {}

  inline void add_flag(const rslc_flag flag) {
    flags = join_flags(flags, flag);
  }

  inline void add_arg(const rslc_arg arg, const std::string value) {
    unsigned long a = static_cast<unsigned long>(arg);
    if (a < static_cast<unsigned long>(MAX_ARGS)) {
      args[a] = value;
    } else {
    }
  }

  inline bool has_errors() const { return !errors.empty(); }

  lexer::token_stream &run_lexer() const;
  syntax::ast &run_syntax_analysis(lexer::token_stream &stream) const;
  codegen::codestream &run_code_generator(syntax::ast &ast) const;

  inline std::shared_ptr<codegen::codestream> compile() const {
    lexer::token_stream &lex = run_lexer();
    if (has_errors())
      return std::shared_ptr<codegen::codestream>();
    syntax::ast &syn = run_syntax_analysis(lex);
    if (has_errors())
      return std::shared_ptr<codegen::codestream>();
    codegen::codestream &strm = run_code_generator(syn);
    return std::make_shared<codegen::codestream>(strm);
  }

  inline friend compiler &operator<<(compiler &c, rslc_error &err) {
    c.errors.push(err);
    return c;
  }

  inline friend compiler &operator>>(compiler &c, rslc_error &targ) {
    if (c.has_errors()) {
      targ = c.errors.front();
      c.errors.pop();
    } else {
      targ = rslc_error::no_error;
    }
    return c;
  }

private:
  err_queue_t errors;
  rslc_flag flags;
  std::string args[static_cast<uint64_t>(MAX_ARGS)];
  std::istream &source;
}; // compiler
}; // namespace rslc

#endif // _RSLC_RSLC
