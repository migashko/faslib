//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/functional/member.hpp>
#include <fas/functional/member_get.hpp>
#include <fas/functional/member_set.hpp>
#include <fas/functional/mem_fun_get.hpp>
#include <fas/functional/mem_fun_set.hpp>
#include <fas/functional/global_fun_get.hpp>
#include <fas/functional/global_fun_set.hpp>
#include <fas/system/nullptr.hpp>
#include <fas/static_check/static_check.hpp>

#include <fas/testing.hpp>
#include <string>
#include <cstring>

struct foo;
const std::string& get_foo1(const foo& f);
void set_foo1(foo& f, const std::string& value);
int get_foo2(const foo& f);
void set_foo2(foo& f, int value);
const char* get_foo3(const foo& f);
void set_foo3(foo& f, const char* value);
const char* get_foo4(const foo& f);
void set_foo4(foo& f, const char* value);


struct foo
{
  std::string foo1;
  int foo2;

  typedef char foo3_type[100];
  typedef char* foo4_type;

  char foo3[100];
  char* foo4;

  foo()
    : foo1("foo1")
    , foo2(2)
    , foo4(new char[100])
  {
    std::strcpy(foo3, "foo3");
    std::strcpy(foo4, "foo4");
  }

  ~foo()
  {
    delete[] foo4;
  }

  const std::string& get_foo1() const { return foo1;}
  void set_foo1(const std::string& value) { foo1 = value;}

  int get_foo2() const { return foo2;}
  void set_foo2(int value) { foo2 = value;}

  const char* get_foo3() const { return foo3;}
  void set_foo3(const char* value) { std::strcpy(foo3, value);}

  const char* get_foo4() const { return foo4;}
  void set_foo4(const char* value) { std::strcpy(foo4, value);}
private:
  foo(const foo&): foo1(""), foo2(0), foo3(), foo4(fas_nullptr) {}
  foo& operator=(const foo&) 
  {
    foo1=""; foo2=0; std::strcpy(foo3, ""); foo4=fas_nullptr;
    return *this;
  }
};

UNIT(member_unit, "")
{
  using namespace ::fas::testing;
  foo f;
  typedef fas::member<foo, std::string, &foo::foo1> get_foo1;
  typedef fas::member<foo, int, &foo::foo2> get_foo2;
  typedef fas::member<foo, foo::foo3_type, &foo::foo3> get_foo3;
  typedef fas::member<foo, foo::foo4_type, &foo::foo4> get_foo4;

  t << equal<assert, std::string> ( get_foo1()(f), "foo1" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, int> ( get_foo2()(f), 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo3()(f), "foo3" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo4()(f), "foo4" ) << FAS_TESTING_FILE_LINE;

  get_foo1()(f) = "foo1-test";
  get_foo2()(f) = 42;
  std::strcpy( get_foo3()(f), "foo3-test" );
  std::strcpy( get_foo4()(f), "foo4-test" );

  t << equal<assert, std::string> ( get_foo1()(f), "foo1-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, int> ( get_foo2()(f), 42 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo3()(f), "foo3-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo4()(f), "foo4-test" ) << FAS_TESTING_FILE_LINE;
}

UNIT(member_get_set_unit, "")
{
  using namespace ::fas::testing;
  foo f;
  const foo& fc = f;
  typedef fas::member_get<foo, std::string, &foo::foo1> get_foo1;
  typedef fas::member_get<foo, int, &foo::foo2> get_foo2;
  typedef fas::member_get<foo, foo::foo3_type, &foo::foo3> get_foo3;
  typedef fas::member_get<foo, foo::foo4_type, &foo::foo4> get_foo4;

  typedef fas::member_set<foo, std::string, &foo::foo1> set_foo1;
  typedef fas::member_set<foo, int, &foo::foo2> set_foo2;
  typedef fas::member_set<foo, foo::foo3_type, &foo::foo3> set_foo3;
  typedef fas::member_set<foo, foo::foo4_type, &foo::foo4> set_foo4;

  t << equal<assert, std::string> ( get_foo1()(f), "foo1" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, int> ( get_foo2()(f), 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo3()(f), "foo3" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo4()(f), "foo4" ) << FAS_TESTING_FILE_LINE;

  set_foo1()(f) = "foo1-test";
  set_foo2()(f) = 42;
  std::strcpy( set_foo3()(f), "foo3-test" );
  std::strcpy( set_foo4()(f), "foo4-test" );

  t << equal<assert, std::string> ( set_foo1()(f), "foo1-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, int> ( set_foo2()(f), 42 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( set_foo3()(f), "foo3-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( set_foo4()(f), "foo4-test" ) << FAS_TESTING_FILE_LINE;

  t << equal<assert, std::string> ( get_foo1()(fc), "foo1-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, int> ( get_foo2()(fc), 42 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo3()(fc), "foo3-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo4()(fc), "foo4-test" ) << FAS_TESTING_FILE_LINE;
}

UNIT(mem_fun_unit, "")
{
  using namespace ::fas::testing;
  foo f;
  const foo& fc = f;
  typedef fas::mem_fun_get<foo, const std::string&, &foo::get_foo1> get_foo1;
  typedef fas::mem_fun_get<foo, int, &foo::get_foo2> get_foo2;
  typedef fas::mem_fun_get<foo, const char*, &foo::get_foo3> get_foo3;
  typedef fas::mem_fun_get<foo, const char*, &foo::get_foo4> get_foo4;

  typedef fas::mem_fun_set<foo, const std::string&, &foo::set_foo1> set_foo1;
  typedef fas::mem_fun_set<foo, int, &foo::set_foo2> set_foo2;
  typedef fas::mem_fun_set<foo, const char*, &foo::set_foo3, char*> set_foo3;
  typedef fas::mem_fun_set<foo, const char*, &foo::set_foo4, char*> set_foo4;
  typedef fas::mem_fun_set<foo, const char*, &foo::set_foo3, foo::foo3_type> set_foo3_arr;
  /* foo::foo3_type temp. buffer char[] */
  typedef fas::mem_fun_set<foo, const char*, &foo::set_foo4, foo::foo3_type> set_foo4_arr;


  t << equal<assert, std::string> ( get_foo1()(f), "foo1" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, int> ( get_foo2()(f), 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo3()(f), "foo3" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo4()(f), "foo4" ) << FAS_TESTING_FILE_LINE;

  set_foo1()(f) = "foo1-test";
  set_foo2()(f) = 42;
  char buffer[256];
  std::strcpy( set_foo3()(f, buffer), "foo3-test" );
  std::strcpy( set_foo4()(f, buffer), "foo4-test" );

  t << equal<assert, std::string> ( get_foo1()(f), "foo1-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, int> ( get_foo2()(f), 42 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo3()(f), "foo3-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo4()(f), "foo4-test" ) << FAS_TESTING_FILE_LINE;

  t << equal<assert, std::string> ( get_foo1()(fc), "foo1-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, int> ( get_foo2()(fc), 42 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo3()(fc), "foo3-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo4()(fc), "foo4-test" ) << FAS_TESTING_FILE_LINE;

  std::strcpy( set_foo3_arr()(f), "foo3-test-array" );
  std::strcpy( set_foo4_arr()(f), "foo4-test-array" );

  t << equal<assert, std::string> ( get_foo3()(fc), "foo3-test-array" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo4()(fc), "foo4-test-array" ) << FAS_TESTING_FILE_LINE;
}


const std::string& get_foo1(const foo& f)
{
  return f.foo1;
}

void set_foo1(foo& f, const std::string& value)
{
  f.foo1 = value;
}


int get_foo2(const foo& f)
{
  return f.foo2;
}

void set_foo2(foo& f, int value)
{
  f.foo2 = value;
}

const char* get_foo3(const foo& f)
{
  return f.foo3;
}

void set_foo3(foo& f, const char* value)
{
  f.set_foo3(value);
}

const char* get_foo4(const foo& f)
{
  return f.foo4;
}

void set_foo4(foo& f, const char* value)
{
  f.set_foo4(value);
}


UNIT(global_fun_unit, "")
{
  using namespace ::fas::testing;
  foo f;
  const foo& fc = f;

  typedef fas::global_fun_get<const foo&, const std::string&, &get_foo1> foo1_getter;
  typedef fas::global_fun_get<const foo&, int, &get_foo2> foo2_getter;
  typedef fas::global_fun_get<const foo&, const char*, &get_foo3> foo3_getter;
  typedef fas::global_fun_get<const foo&, const char*, &get_foo4> foo4_getter;

  t << equal<assert, std::string> ( get_foo1(f), "foo1" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( foo1_getter()(f), "foo1" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, int> ( get_foo2(f), 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, int> ( foo2_getter()(f), 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo3(f), "foo3" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( foo3_getter()(f), "foo3" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( get_foo4(f), "foo4" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( foo4_getter()(f), "foo4" ) << FAS_TESTING_FILE_LINE;

  typedef fas::global_fun_set<foo&, const std::string&, &set_foo1> foo1_setter;
  typedef fas::global_fun_set<foo&, int, &set_foo2> foo2_setter;
  typedef fas::global_fun_set<foo&, const char*, &set_foo3, char*> foo3_setter;
  typedef fas::global_fun_set<foo&, const char*, &set_foo4, char*> foo4_setter;

  set_foo1(f, "");
  foo1_setter()(f) = "foo1-test";
  set_foo2(f, 1);
  foo2_setter()(f) = 42;
  char buffer[256];
  std::strcpy( foo3_setter()(f, buffer), "foo3-test" );
  std::strcpy( foo4_setter()(f, buffer), "foo4-test" );

  t << equal<assert, std::string> ( foo1_getter()(f), "foo1-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, int> ( foo2_getter()(f), 42 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( foo3_getter()(f), "foo3-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( foo4_getter()(f), "foo4-test" ) << FAS_TESTING_FILE_LINE;

  t << equal<assert, std::string> ( foo1_getter()(fc), "foo1-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, int> ( foo2_getter()(fc), 42 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( foo3_getter()(fc), "foo3-test" ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, std::string> ( foo4_getter()(fc), "foo4-test" ) << FAS_TESTING_FILE_LINE;
}

BEGIN_SUITE(access_suite, "")
  ADD_UNIT(member_unit)
  ADD_UNIT(member_get_set_unit)
  ADD_UNIT(mem_fun_unit)
  ADD_UNIT(global_fun_unit)
END_SUITE(access_suite)

BEGIN_TEST
  RUN_SUITE(access_suite)
END_TEST


