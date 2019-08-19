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
#include <cmath>
#include <sstream>
#include <limits>


#define FAS_TESTING_FILE_LINE " " << __FILE__ << ": " << __LINE__
#define FAS_FL FAS_TESTING_FILE_LINE

namespace fas{ namespace testing{

struct trace;
struct expect;
struct assert;
struct critical;
struct crash;

template<typename L, typename R>
std::string compare_message(const std::string& msg, const L& left, const std::string& op, const R& right);

template<typename T>
bool is_float_equal(const T& left, const T& right);

template<typename M>
struct statement
{
protected:
  statement(const statement<M>&):result(false), text(){}
  statement& operator=(const statement<M>&){result=false; text.clear(); return *this;}
public:
  bool result;
  std::string text;
  explicit statement(bool res, const std::string& txt = "" ): result(res), text(txt) {}
  ~statement() {}
};

template<typename M = assert, typename T = empty_type>
struct equal: statement<M>
{
  template<typename L, typename R>
  equal(const L& left, const R& right)
    : statement<M>(
        static_cast<const T&>(left) == static_cast<const T&>(right),
        compare_message("Equal statement. ", static_cast<const T&>(left), "!=", static_cast<const T&>(right))
      )
  {}

  template<typename L, typename R>
  equal(const L& left, const R& right, const std::string& txt)
    : statement<M>(
        static_cast<const T&>(left) == static_cast<const T&>(right),
        compare_message(txt, static_cast<const T&>(left), "!=", static_cast<const T&>(right))
      )
  {}
};

template<typename M, typename T, bool neg>
struct float_equal: statement<M>
{
  template<typename L, typename R>
  float_equal(const L& left, const R& right, const std::string& txt)
    : statement<M>(
        is_float_equal(
          static_cast<const T&>(left),
          static_cast<const T&>(right)
        ),
        compare_message(
          txt.empty() ? std::string("Equal statement. ") : txt,
          left,
          neg ? std::string("--") : std::string("!="),
          right
        )
    )
  {}
};

template<typename M>
struct equal<M, float>: float_equal<M, float, false>
{
  template<typename L, typename R>
  equal(const L& left, const R& right)
    : float_equal<M, float, false>(left, right, "Equal statement. ")
  {}

  template<typename L, typename R>
  equal(const L& left, const R& right, const std::string& txt)
    : float_equal<M, float, false>(left, right, txt)
  {}
};

template<typename M>
struct equal<M, double>: float_equal<M, double, false>
{
  template<typename L, typename R>
  equal(const L& left, const R& right)
    : float_equal<M, double, false>(left, right, "Equal statement. ")
  {}

  template<typename L, typename R>
  equal(const L& left, const R& right, const std::string& txt)
    : float_equal<M, double, false>(left, right, txt)
  {}
};

template<typename M>
struct equal<M, long double>: float_equal<M, long double, false>
{
  template<typename L, typename R>
  equal(const L& left, const R& right)
    : float_equal<M, long double, false>(left, right, "Equal statement. ")
  {}

  template<typename L, typename R>
  equal(const L& left, const R& right, const std::string& txt)
    : float_equal<M, long double, false>(left, right, txt)
  {}
};

template<typename M>
struct equal<M, empty_type>: statement<M>
{
  template<typename L, typename R>
  equal(const L& left, const R& right)
    : statement<M>(
      left == right,
      compare_message("Equal statement. ", left, "!=", right)
    )
  {}

  template<typename L, typename R>
  equal(const L& left, const R& right, const std::string& txt)
    : statement<M>(
      left == right,
      compare_message(txt, left, "!=", right)
    )
  {}
};

template<typename M = assert, typename T = empty_type>
struct not_equal: statement<M>
{
  template<typename L, typename R>
  not_equal(const L& left, const R& right)
    : statement<M>(
      static_cast<const T&>(left) != static_cast<const T&>(right),
      compare_message("Not equal statement. ", static_cast<const T&>(left), "==", static_cast<const T&>(right) )
    )
  {}

  template<typename L, typename R>
  not_equal(const L& left, const R& right, const std::string& txt)
    : statement<M>(
      static_cast<const T&>(left) != static_cast<const T&>(right),
      compare_message(txt, static_cast<const T&>(left), "==", static_cast<const T&>(right) )
    )
  {}
};


template<typename M>
struct not_equal<M, float>: float_equal<M, float, true>
{
  template<typename L, typename R>
  not_equal(const L& left, const R& right)
    : float_equal<M, float, true>(left, right, "Not equal statement. ")
  {}

  template<typename L, typename R>
  not_equal(const L& left, const R& right, const std::string& txt)
    : float_equal<M, float, true>(left, right, txt)
  {}
};

template<typename M>
struct not_equal<M, double>: float_equal<M, double, true>
{
  template<typename L, typename R>
  not_equal(const L& left, const R& right)
    : float_equal<M, double, true>(left, right, "Not equal statement. ")
  {}

  template<typename L, typename R>
  not_equal(const L& left, const R& right, const std::string& txt)
    : float_equal<M, double, true>(left, right, txt)
  {}
};

template<typename M>
struct not_equal<M, empty_type>: statement<M>
{
  template<typename L, typename R>
  not_equal(const L& left, const R& right)
    : statement<M>(
      left != right,
      compare_message("Not equal statement. ", left, "==", right)
    )
  {}

  template<typename L, typename R>
  not_equal(const L& left, const R& right, const std::string& txt)
    : statement<M>(
      left != right,
      compare_message(txt, left, "==", right)
    )
  {}
};

template<typename M = assert, typename T = empty_type>
struct less: statement<M>
{
  template<typename L, typename R>
  less(const L& left, const R& right)
    : statement<M>(
        static_cast<const T&>(left) < static_cast<const T&>(right),
        compare_message("Less statement. ", static_cast<const T&>(left), ">=", static_cast<const T&>(right) )
      )
  {}

  template<typename L, typename R>
  less(const L& left, const R& right, const std::string& txt)
    : statement<M>(
        static_cast<const T&>(left) < static_cast<const T&>(right),
        compare_message(txt, static_cast<const T&>(left), ">=", static_cast<const T&>(right) )
      )
  {}
};

template<typename M>
struct less<M, empty_type>: statement<M>
{
  template<typename L, typename R>
  less(const L& left, const R& right)
    : statement<M>(
      left < static_cast<const L&>(right),
      compare_message("Less statement. ", left, ">=", right)
    )
  {}

  template<typename L, typename R>
  less(const L& left, const R& right, const std::string& txt)
    : statement<M>(
      left <  static_cast<const L&>(right),
      compare_message(txt, left, ">=", right)
    )
  {}
};

template<typename M = assert, typename T = empty_type>
struct less_equal: statement<M>
{
  template<typename L, typename R>
  less_equal(const L& left, const R& right)
    : statement<M>(
        static_cast<const T&>(left) <= static_cast<const T&>(right),
        compare_message("Less equal statement. ", static_cast<const T&>(left), ">", static_cast<const T&>(right) )
      )
  {}

  template<typename L, typename R>
  less_equal(const L& left, const R& right, const std::string& txt)
    : statement<M>(
        static_cast<const T&>(left) <= static_cast<const T&>(right),
        compare_message(txt, static_cast<const T&>(left), ">", static_cast<const T&>(right) )
      )
  {}
};

template<typename M>
struct less_equal<M, empty_type>: statement<M>
{
  template<typename L, typename R>
  less_equal(const L& left, const R& right)
    : statement<M>(
      left <= right,
      compare_message("Less equal statement. ", left, ">", right)
    )
  {}

  template<typename L, typename R>
  less_equal(const L& left, const R& right, const std::string& txt)
    : statement<M>(
      left <= right,
      compare_message(txt, left, ">", right)
    )
  {}
};

template<typename M = assert, typename T = empty_type>
struct greater: statement<M>
{
  template<typename L, typename R>
  greater(const L& left, const R& right)
    : statement<M>(
        static_cast<const T&>(left) > static_cast<const T&>(right),
        compare_message("Greater statement. ", static_cast<const T&>(left), "<=", static_cast<const T&>(right) )
      )
  {}

  template<typename L, typename R>
  greater(const L& left, const R& right, const std::string& txt)
    : statement<M>(
        static_cast<const T&>(left) > static_cast<const T&>(right),
        compare_message(txt, static_cast<const T&>(left), "<=", static_cast<const T&>(right) )
      )
  {}
};

template<typename M>
struct greater<M, empty_type>: statement<M>
{
  template<typename L, typename R>
  greater(const L& left, const R& right)
    : statement<M>(
      left > right,
      compare_message("Greater statement. ", left, "<=", right)
    )
  {}

  template<typename L, typename R>
  greater(const L& left, const R& right, const std::string& txt)
    : statement<M>(
      left > right,
      compare_message(txt, left, "<=", right)
    )
  {}
};

template<typename M = assert, typename T = empty_type>
struct greater_equal: statement<M>
{
  template<typename L, typename R>
  greater_equal(const L& left, const R& right)
    : statement<M>(
        static_cast<const T&>(left) >= static_cast<const T&>(right),
        compare_message("Greater equal statement. ", static_cast<const T&>(left), "<", static_cast<const T&>(right) )
      )
  {}

  template<typename L, typename R>
  greater_equal(const L& left, const R& right, const std::string& txt)
    : statement<M>(
        static_cast<const T&>(left) >= static_cast<const T&>(right),
        compare_message(txt, static_cast<const T&>(left), "<", static_cast<const T&>(right) )
      )
  {}
};

template<typename M>
struct greater_equal<M, empty_type>: statement<M>
{
  template<typename L, typename R>
  greater_equal(const L& left, const R& right)
    : statement<M>(
      left >= right,
      compare_message("Greater equal statement. ", left, "<", right)
    )
  {}

  template<typename L, typename R>
  greater_equal(const L& left, const R& right, const std::string& txt)
    : statement<M>(
      left >= right,
      compare_message(txt, left, "<", right)
    )
  {}
};

template<typename M = assert>
struct equal_str: statement<M>
{
  equal_str(const std::string& left, const std::string& right): statement<M>( left == right, compare_message("Equal statement. ", left, "!=", right) ) {}

  equal_str(const std::string& left, const std::string& right, const std::string& txt): statement<M>( left == right, compare_message(txt, left, "!=", right) ) {}

  template<typename R>
  equal_str(const std::string& left, R right): statement<M>( left == right, compare_message("Equal statement. ", left, "!=", right) ) {}

  template<typename R>
  equal_str(const std::string& left, R right, const std::string& txt): statement<M>( left == right, compare_message(txt, left, "!=", right) ) {}
};

template<typename M = assert>
struct is_true: statement<M>
{
  explicit is_true(bool value): statement<M>(value, "Is true statement. ") {}
  is_true(bool value, const std::string& txt): statement<M>(value, txt) {}
};

template<typename M = assert>
struct is_false: statement<M>
{
  explicit is_false(bool value): statement<M>(!value, "Is false statement. "){}
  is_false(bool value, const std::string& txt): statement<M>(!value, txt){}
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
   explicit message(const std::string& txt)
    : info< trace, _message_ >(true, txt)
   {}
};

struct warning: info< trace, _warning_ > { explicit warning(const std::string& txt): info< trace, _warning_ >(false, txt) {} };

struct error: info< expect, _error_ > { explicit error(const std::string& txt): info< expect, _error_ >(false, txt) {} };

struct fail: info< assert, _fail_ > { explicit fail(const std::string& txt): info< assert, _fail_ >(false, txt) {} };

struct fatal: info< critical, _fatal_> { explicit fatal(const std::string& txt): info< critical, _fatal_ >(false, txt) {} };

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
void os_write(std::ostream& s, const V& v, fas::type_list<V, L> ) { s << std::boolalpha << v; }

template<typename V, typename H, typename L>
void os_write(std::ostream& s, const V& v, fas::type_list<H, L> ) { os_write(s, v, L() ); }

template<typename L, typename R>
std::string compare_message(const std::string& msg, const L& left, const std::string& op, const R& right)
{
  std::stringstream ss;
  ss << msg << "( ";
  os_write(ss, left, ostream_types() );
  ss << op;
  os_write(ss, right, ostream_types() );
  ss << " ). ";
  return ss.str();
}

template<typename T>
bool is_float_equal(const T& left, const T& right)
{
  return std::fabs(left - right) < std::numeric_limits<T>::epsilon();
}


}}

#endif
