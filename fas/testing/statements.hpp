//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TESTING_STATEMENTS_HPP
#define FAS_TESTING_STATEMENTS_HPP

#include <fas/testing/tags.hpp>
#include <fas/typemanip/empty_type.hpp>
#include <string>

#define FAS_TESTING_FILE_LINE __FILE__ << ": " << __LINE__

namespace fas{ namespace testing{

struct trace;
struct expect;
struct assert;
struct critical;

template<typename M>
struct statement
{
protected:
  statement(const statement<M>&){}
public:
  bool result;
  std::string text;
  statement(bool result, const std::string& text = "" ): result(result), text(text) {}
  ~statement() {}
};

template<typename M = assert, typename T = empty_type>
struct equal: statement<M>
{
  equal(T left, T right): statement<M>( left == right, "Equal statement. " ) {}
  equal(T left, T right, const std::string& text): statement<M>( left == right, text ) {}
};

template<typename M>
struct equal<M, empty_type>: statement<M>
{
  template<typename L, typename R>
  equal(L left, R right): statement<M>( left == right, "Equal statement. " ) {}

  template<typename L, typename R>
  equal(L left, R right, const std::string& text): statement<M>( left == right, text ) {}
};

template<typename M = assert, typename T = empty_type>
struct not_equal: statement<M>
{
  not_equal(T left, T right): statement<M>( left != right, "Not equal statement. " ) {}
  not_equal(T left, T right, const std::string& text): statement<M>( left != right, text ) {}
};

template<typename M>
struct not_equal<M, empty_type>: statement<M>
{
  template<typename L, typename R>
  not_equal(L left, R right): statement<M>( left != right, "Not equal statement. " ) {}

  template<typename L, typename R>
  not_equal(L left, R right, const std::string& text): statement<M>( left != right, text ) {}
};


template<typename M = assert>
struct equal_str: statement<M>
{

  equal_str(std::string left, std::string right): statement<M>( left == right, "Equal string statement. " ) {}

  equal_str(std::string left, std::string right, const std::string& text): statement<M>( left == right, text ) {}

  template<typename R>
  equal_str(std::string left, R right): statement<M>( left == right, "Equal string statement. " ) {}

  template<typename R>
  equal_str(std::string left, R right, const std::string& text): statement<M>( left == right, text ) {}
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

struct nothing{};

template<typename M = expect, typename F = _message_ >
struct info: statement<M>
{
  typedef void (*manip)( F );
  info(bool result, const std::string& text)
    : statement<M>(result, text)
  {
  }
};

struct message
  : info< trace, _message_ >
{
   message(const std::string& text)
    : info< trace, _message_ >(true, text)
   {}
};

struct warning: info< trace, _warning_ > { warning(const std::string& text): info< trace, _warning_ >(false, text) {} };

struct error: info< expect, _error_ > { error(const std::string& text): info< expect, _error_ >(false, text) {} };

struct fail: info< assert, _fail_ > { fail(const std::string& text): info< assert, _fail_ >(false, text) {} };

struct fatal: info< critical, _fatal_> { fatal(const std::string& text): info< critical, _fatal_ >(false, text) {} };


}}

#endif
