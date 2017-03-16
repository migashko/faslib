//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TESTING_STATEMENTS_HPP
#define FAS_TESTING_STATEMENTS_HPP

#include <fas/testing/tags.hpp>
#include <fas/typemanip/empty_type.hpp>
#include <fas/type_list.hpp>
#include <string>
#include <sstream>

#define FAS_TESTING_FILE_LINE " " << __FILE__ << ": " << __LINE__
#define FAS_FL FAS_TESTING_FILE_LINE

namespace fas{ namespace testing{

struct trace;
struct expect;
struct assert;
struct critical;

template<typename L, typename R>
std::string equal_message(std::string msg, const L& left, std::string op, const R& right);

template<typename M>
struct statement
{
protected:
  statement(const statement<M>&){}
public:
  bool result;
  std::string text;
  statement(bool res, const std::string& txt = "" ): result(res), text(txt) {}
  ~statement() {}
};

template<typename M = assert, typename T = empty_type>
struct equal: statement<M>
{
  equal(const T& left, const T& right): statement<M>( left == right, equal_message("Equal statement. ", left, "!=", right) ) {}
  equal(const T& left, const T& right, const std::string& text): statement<M>( left == right, equal_message(text, left, "!=", right) ) {}
};

template<typename M>
struct equal<M, empty_type>: statement<M>
{
  template<typename L, typename R>
  equal(const L& left, const R& right): statement<M>( left == right, equal_message("Equal statement. ", left, "!=", right) ) {}

  template<typename L, typename R>
  equal(const L& left, const R& right, const std::string& text): statement<M>( left == right, equal_message(text, left, "!=", right) ) {}
};

template<typename M = assert, typename T = empty_type>
struct not_equal: statement<M>
{
  not_equal(const T& left, const T& right): statement<M>( left != right, equal_message("Not equal statement. ", left, "==", right) ) {}
  not_equal(const T& left, const T& right, const std::string& text): statement<M>( left != right, equal_message(text, left, "==", right) ) {}
};

template<typename M>
struct not_equal<M, empty_type>: statement<M>
{
  template<typename L, typename R>
  not_equal(const L& left, const R& right): statement<M>( left != right, equal_message("Not equal statement. ", left, "==", right) ) {}

  template<typename L, typename R>
  not_equal(const L& left, const R& right, const std::string& text): statement<M>( left != right, equal_message(text, left, "==", right) ) {}
};

template<typename M = assert, typename T = empty_type>
struct less: statement<M>
{
  less(const T& left, const T& right): statement<M>( left < right, equal_message("Less statement. ", left, ">=", right) ) {}
  less(const T& left, const T& right, const std::string& text): statement<M>( left == right, equal_message(text, left, ">=", right) ) {}
};

template<typename M>
struct less<M, empty_type>: statement<M>
{
  template<typename L, typename R>
  less(const L& left, const R& right): statement<M>( left < right, equal_message("Less statement. ", left, ">=", right) ) {}

  template<typename L, typename R>
  less(const L& left, const R& right, const std::string& text): statement<M>( left == right, equal_message(text, left, ">=", right) ) {}
};


template<typename M = assert>
struct equal_str: statement<M>
{

  equal_str(std::string left, std::string right): statement<M>( left == right, equal_message("Equal statement. ", left, "!=", right) ) {}

  equal_str(std::string left, std::string right, const std::string& text): statement<M>( left == right, equal_message(text, left, "!=", right) ) {}

  template<typename R>
  equal_str(std::string left, R right): statement<M>( left == right, equal_message("Equal statement. ", left, "!=", right) ) {}

  template<typename R>
  equal_str(std::string left, R right, const std::string& text): statement<M>( left == right, equal_message(text, left, "!=", right) ) {}
};

template<typename M = assert>
struct is_true: statement<M>
{
  is_true(bool value): statement<M>(value, "Is true statement. ") {}
  is_true(bool value, const std::string& text): statement<M>(value, text) {}
};

template<typename M = assert>
struct is_false: statement<M>
{
  is_false(bool value): statement<M>(!value, "Is false statement. "){}
  is_false(bool value, const std::string& text): statement<M>(!value, text){}
};

template<typename M = expect, typename F = _message_ >
struct info: statement<M>
{
  typedef void (*manip)( F );
  info(bool res, const std::string& txt)
    : statement<M>(res, txt)
  {
  }
};

struct message
  : info< trace, _message_ >
{
   message(const std::string& txt)
    : info< trace, _message_ >(true, txt)
   {}
};

struct warning: info< trace, _warning_ > { warning(const std::string& txt): info< trace, _warning_ >(false, txt) {} };

struct error: info< expect, _error_ > { error(const std::string& txt): info< expect, _error_ >(false, txt) {} };

struct fail: info< assert, _fail_ > { fail(const std::string& txt): info< assert, _fail_ >(false, txt) {} };

struct fatal: info< critical, _fatal_> { fatal(const std::string& txt): info< critical, _fatal_ >(false, txt) {} };

typedef fas::type_list_n<
  std::string,
  const char*, const signed char*, const unsigned char*,
  bool,
  short, unsigned short,
  int,   unsigned int,
  long,  unsigned long,
  float, double, long double,
  char, signed char, unsigned char
>::type ostream_types;

template<typename V>
void os_write(std::ostream& s, const V&, fas::empty_list ) { s << "?"; }

template<typename V, typename L>
void os_write(std::ostream& s, const V& v, fas::type_list<V, L> ) { s << v; }

template<typename V, typename H, typename L>
void os_write(std::ostream& s, const V& v, fas::type_list<H, L> ) { os_write(s, v, L() ); }

template<typename L, typename R>
std::string equal_message(std::string msg, const L& left, std::string op, const R& right)
{
  std::stringstream ss;
  ss << msg << "( ";
  os_write(ss, left, ostream_types() );
  ss << op;
  os_write(ss, right, ostream_types() );
  ss << " ). ";
  return ss.str();
}

}}

#endif
