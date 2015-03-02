//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TESTING_SUITE_HPP
#define FAS_TESTING_SUITE_HPP

#include <fas/testing/statements.hpp>
#include <fas/testing/formatting.hpp>
#include <fas/testing/exceptions.hpp>
#include <fas/testing/suite_counts.hpp>
#include <fas/testing/f_unit_run.hpp>
#include <fas/testing/unit_status.hpp>
#include <fas/testing/tags.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/type.hpp>
#include <fas/aop/value.hpp>
#include <fas/aop/stub.hpp>
#include <fas/aop/group.hpp>
#include <fas/aop/aspect_class.hpp>
#include <fas/aop/tag.hpp>

#include <sstream>
#include <iostream>

namespace fas{ namespace testing{


template<typename A = ::fas::aspect<> >
class suite
  : public aspect_class< A>
{

public:
  typedef suite<A> self;
  typedef aspect_class< A> super;

  typedef typename super::aspect aspect;
  typedef typename aspect::template select_group<_units_>::type unit_tag_list;

public:

  suite(const std::string& name = "", const std::string& desc = "")
    : _out(std::cout)
    , _name(name)
    , _desc(desc)
    , _status(unit_status::noerror)
    , _unit_errors(0)
    , _unit_fails(0)
    , _unit_fatals(0)
    , _unit_statements(0)
  {
  }

  suite(std::ostream& os, const std::string& name = "", const std::string& desc = "")
    : _out(os)
    , _name(name)
    , _desc(desc)
    , _status(unit_status::noerror)
    , _unit_count(0)
    , _unit_errors(0)
    , _unit_fails(0)
    , _unit_fatals(0)
    , _unit_statements(0)
  {
  }

  std::ostream& out() { return _out;}

  const std::stringstream& stub() const { return _stub;}

  template<typename U>
  void unit_begin(U& /*u*/)
  {
    _unit_count++;
    _unit_errors = 0;
    _unit_fails = 0;
    _unit_fatals = 0;
    _unit_statements = 0;
    _status = unit_status::noerror;
  }

  template<typename U>
  void unit_end(U& u)
  {
    u.counts().errors += _unit_errors;
    u.counts().fails += _unit_fails;
    u.counts().fatals += _unit_fatals;
    u.counts().statements += _unit_statements;
    if ( _status == unit_status::noerror )
      _suite_counts.units_passed++;
    _suite_counts += u.counts();
    _suite_counts.units++;
  }

  void _status_check()
  {
    if ( _status == unit_status::error )
    {
    }
    else if (_status == unit_status::fail)
    {
      throw fail_error();
    }
    else if (_status == unit_status::fatal)
    {
      throw fatal_error();
    }
  }

  void statement_begin()
  {
    ++_unit_statements;
    _status_check();
    _status = unit_status::noerror;
  }

  void operator << ( void (*)( _stop_ ) )
  {
    _status_check();
  }

  std::ostream& operator << ( const statement<expect>& st )
  {
    statement_begin();
    if ( st.result == false)
    {
      _unit_errors++;
      _status = unit_status::error;
      _out << std::endl << ERROR_MESSAGE << st.text;
      return _out;
    }
    return _stub;
  }

  std::ostream& operator << ( const statement<assert>& st )
  {
    statement_begin();
    if ( st.result == false)
    {
      _unit_fails++;
      _status = unit_status::fail;
      _out << std::endl << FAIL << st.text;
      return _out;
    }
    return _stub;
  }

  std::ostream& operator << ( const statement<critical>& st )
  {
    statement_begin();
    if ( st.result == false)
    {
      _status = unit_status::fatal;
      _unit_fatals++;
      _out << std::endl << FATAL << st.text;
      return _out;
    }
    return _stub;
  }

  template<typename F>
  std::ostream& operator << ( const info<trace, F>& st )
  {
    _status_check();
    typename info<expect, F>::manip manip = 0;
    _out << std::endl << manip << st.text;
    return _out;
  }

  template<typename F>
  std::ostream& operator << ( const info<expect, F>& st )
  {
    _status_check();
    _status = unit_status::error;
    typename info<expect, F>::manip manip = 0;
    _out << std::endl << manip << st.text;
    return _out;
  }

  template<typename F>
  std::ostream& operator << ( const info<assert, F>& st )
  {
    _status_check();
    _status = unit_status::fail;
    _unit_fails++;
    typename info<assert, F>::manip manip = 0;
    _out << std::endl << manip << st.text;
    return _out;
  }

  template<typename F>
  std::ostream& operator << ( const info<critical, F>& st )
  {
    _status_check();
    _status = unit_status::fatal;
    _unit_fatals++;
    typename info<critical, F>::manip manip = 0;
    _out << std::endl << manip << st.text;
    return _out;
  }

  std::ostream& operator <<( nothing )
  {
    return _out;
  }

  operator bool () const 
  { 
    return   _suite_counts.errors == 0 
          && _suite_counts.fails  == 0 
          && _suite_counts.fatals == 0;
  }

  bool run()
  {
    return _run(*this);
  }

  template<typename T>
  bool _run(T& t)
  {
    _unit_count = 0;
    _unit_errors = 0;
    _unit_fails = 0;
    _unit_fatals = 0;
    _unit_statements = 0;

    _suite_counts.units_total = size();
    _out << SUITE_BEG << size() << " tests";
    if (!_name.empty()) _out << " from " << _name;
    _out << ".";

    try
    {
      super::get_aspect().template getg<_units_>().for_each(t, f_unit_run() );
    }
    catch(const fail_error& )
    {
    }
    catch(const fatal_error& )
    {
    }

    _out << std::endl;

    if ( *this )
    {
      _out << SUITE_END << std::endl;
      _out << PASSED << _suite_counts.units_passed << " tests." << std::endl;
    }
    else
    {
      _out << SUITE_FAIL << _name << ". " << _desc << std::endl;
      _out << PASSED << _suite_counts.units_passed << " tests." << std::endl;
      _out << FAIL << _suite_counts.units - _suite_counts.units_passed << " tests." << std::endl;

    }

    return *this;
  }

  int size() const { return length<unit_tag_list>::value;};
  int count() const { return _suite_counts.units; }

  int errors() const { return _suite_counts.errors; }
  int fails() const { return _suite_counts.fails; }
  int fatals() const { return _suite_counts.fatals; }

  const suite_counts& counts() const { return _suite_counts; };

private:

  std::ostream& _out;
  std::stringstream _stub;

  std::string _name;
  std::string _desc;
  unit_status::type _status;

  int _unit_count;
  int _unit_errors;
  int _unit_fails;
  int _unit_fatals;
  int _unit_statements;

  suite_counts _suite_counts;
};

}}

#include <fas/aop/aspect.hpp>

#define GET_REF(name) t.get_aspect().template get<name>()
#define GET_TYPE(name) typename T::aspect::template advice_cast<name>::type

#define BEGIN_UNIT_LIST(name) struct name##_unit_list: ::fas::type_list_n< ::fas::stub< ::fas::testing::_suite_stub_>
#define END_UNIT_LIST(name) >::type {};

 
#define BEGIN_SUITE(name, desc)\
  inline const char* name##_suite_desc() { return desc;}\
  struct name##_suite_aspect: ::fas::aspect< ::fas::type_list_n< ::fas::stub< ::fas::testing::_suite_stub_>

#define ADD_UNIT(name) ,name##_type_list
#define ADD_CLASS(name) , ::fas::advice<name, name>
#define ADD_ADVICE(tag, name) , ::fas::advice<tag, name>
#define ADD_VALUE(tag, name) , ::fas::value<tag, name>
#define ADD_TYPE(tag, name) , ::fas::type<tag, name>
#define ADD_GROUP(tag, tag_list) , ::fas::group<tag, tag_list>
#define ADD_STUB(tag) , ::fas::stub<tag>
#define ADD_ASPECT(aspect) , aspect
#define ADD_UNIT_LIST(name) , name##_unit_list

#define END_SUITE(name) >::type > {}; \
struct name##_suite: ::fas::testing::suite<name##_suite_aspect> {\
  typedef ::fas::testing::suite<name##_suite_aspect> super;\
  bool run() { return super::_run(*this); }\
  name##_suite(const std::string& name = "", const std::string& desc = ""): super(name, desc) {}\
  name##_suite(std::ostream& os, const std::string& name = "", const std::string& desc = ""): super(os, name, desc) {}\
};\
::fas::testing::suite_counts name##_suite_run(int , char*[])\
{\
  name##_suite s(#name, name##_suite_desc() );\
  s.run(); \
  return s.counts();\
}



#endif

