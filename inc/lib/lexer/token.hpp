#ifndef _RSLC_LEXER_TOKEN
#define _RSLC_LEXER_TOKEN

#include <iostream>
#include <string>
#include <variant>

namespace rslc {
namespace lexer {

template <typename Self> class token_base {
public:
  inline Self &_impl() { return static_cast<Self &>(*this); }
  inline const std::string name() const { return Self::name; }
  inline const std::string content() const { return _content; }
  inline const size_t lineno() const { return _lineno; }
  friend Self;

private:
  inline token_base(std::string content, size_t lineno)
      : _content{content}, _lineno{lineno} {}
  std::string _content;
  size_t _lineno;
}; // token_base

struct token_brace : token_base<token_brace> {
  inline token_brace(char cnt, int lineno)
      : token_base(std::string(1, cnt), lineno), opening{cnt == '{'} {}

  bool opening;
  inline const static std::string name = "TOKEN_BRACE";
};

struct token_text : token_base<token_text> {
  inline token_text(std::string name, int lineno) : token_base(name, lineno) {}
  inline const static std::string name = "TOKEN_NAME";
};

struct token_colon : token_base<token_colon> {
  inline token_colon(int lineno) : token_base(":", lineno) {}
  inline const static std::string name = "TOKEN_COLON";
};

struct token_comma : token_base<token_comma> {
  inline token_comma(int lineno) : token_base(",", lineno) {}
  inline const static std::string name = "TOKEN_COMMA";
};

struct token_bracket : token_base<token_bracket> {
  inline token_bracket(char cnt, int lineno)
      : token_base(std::string(1, cnt), lineno), opening{cnt == '('} {}

  bool opening;
  inline const static std::string name = "TOKEN_BRACKET";
};

struct token_eof : token_base<token_eof> {
  inline token_eof(int lineno) : token_base("", lineno) {}
  inline const static std::string name = "TOKEN_EOF";
};

struct token_invalid : token_base<token_invalid> {
  inline token_invalid(int lineno) : token_base("", lineno) {}
  inline const static std::string name = "TOKEN_INVALID";
};

using token = std::variant<token_brace, token_text, token_colon, token_comma,
                           token_bracket, token_eof, token_invalid>;

inline std::ostream &operator<<(std::ostream &s, token &t) {
  std::visit(
      [&s](auto &arg) {
        s << arg.name << " `" << arg.content() << "` at line " << arg.lineno();
      },
      t);
  return s;
}

struct single_token_visitor {
  template <typename TOut, typename TIn, typename Fun>
  inline TOut operator()(TOut fallback, Fun f) {
    return [&f, &fallback](token &t) {
      if constexpr (std::holds_alternative<TIn>(t)) {
        return f(std::get<TIn>(t));
      } else {
        return fallback;
      }
    };
  }

  template <typename TIn, typename Fun> inline void operator()(Fun f) {
    [&f](token &t) {
      if constexpr (std::holds_alternative<TIn>(t))
        f(std::get<TIn>(t));
    };
  }
};

template <typename TOut, typename TIn, typename Fun>
inline TOut visit_token(token &t, TOut fallback, Fun f) {
  single_token_visitor v;
  return v(fallback, f)(t);
}

template <typename TIn, typename Fun> inline void visit_token(token &t, Fun f) {
  single_token_visitor v;
  v(f)(t);
}

using visitor = single_token_visitor;

} // namespace lexer
} // namespace rslc

#endif // _RSLC_LEXER_TOKEN
