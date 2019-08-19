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

#include <fas/system/nullptr.hpp>
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

  ~suite() {}

  suite(const std::string& name = "", const std::string& desc = "")
    : _out(std::cout)
    , _stub()
    , _name(name)
    , _desc(desc)
    , _status(unit_status::noerror)
    , _unit_counts()
    , _suite_counts()
    , _argc()
    , _argv()
  {
  }

  explicit suite(std::ostream& os, const std::string& name = "", const std::string& desc = "")
    : _out(os)
    , _stub()
    , _name(name)
    , _desc(desc)
    , _status(unit_status::noerror)
    , _unit_counts()
    , _suite_counts()
    , _argc()
    , _argv()
  {
  }

  std::ostream& out() { return _out;}

  const std::stringstream& stub() const { return _stub;}

  template<typename U>
  void unit_skip(U& /*u*/)
  {
    _suite_counts.units_skip++;
  }

  template<typename U>
  void unit_begin(U& /*u*/)
  {
    _unit_counts = unit_counts();
    _status = unit_status::noerror;
  }

  template<typename U>
  void unit_end(U& )
  {
    _suite_counts += _unit_counts;
  }

  void _status_check() const
  {
    if (_unit_counts.fails != 0)
      throw fail_error();
    else if ( _unit_counts.fatals != 0 || _unit_counts.crash )
      throw fatal_error();
  }

  void statement_begin()
  {
    ++_unit_counts.statements;
    _status_check();
  }

  void operator << ( void (*)( _stop_ ) )
  {
    _status_check();
  }

  void operator <<( void (*)( _nothing_ ) )
  {
  }

  std::ostream& operator <<( void (*)( _flush_ ) )
  {
    _out.flush();
    return _out;
  }


  std::ostream& operator << ( const statement<expect>& st )
  {
    this->statement_begin();
    if ( st.result == false)
    {
      _unit_counts.errors++;
      this->set_status_(unit_status::error);
      _out << std::endl << ERROR_MESSAGE << st.text;
      return _out;
    }
    return _stub;
  }

  std::ostream& operator << ( const statement<assert>& st )
  {
    this->statement_begin();
    if ( st.result == false)
    {
      _unit_counts.fails++;
      this->set_status_(unit_status::fail);
      _out << std::endl << FAIL << st.text;
      return _out;
    }
    return _stub;
  }

  std::ostream& operator << ( const statement<critical>& st )
  {
    this->statement_begin();
    if ( st.result == false)
    {
      this->set_status_(unit_status::fatal);
      _unit_counts.fatals++;
      _out << std::endl << FATAL << st.text;
      return _out;
    }
    return _stub;
  }

  std::ostream& operator << ( const statement<crash>& st )
  {
    this->statement_begin();
    if ( st.result == false)
    {
      this->set_status_(unit_status::fatal);
      _unit_counts.crash = true;
      _out << std::endl << CRASH << st.text;
      return _out;
    }
    return _stub;
  }

  template<typename F>
  std::ostream& operator << ( const info<trace, F>& st )
  {
    _status_check();
    typename info<expect, F>::manip manip = fas_nullptr;
    _out << std::endl << manip << st.text;
    return _out;
  }

  template<typename F>
  std::ostream& operator << ( const info<expect, F>& st )
  {
    _status_check();
    this->set_status_(unit_status::error);
    _unit_counts.errors++;
    typename info<expect, F>::manip manip = fas_nullptr;
    _out << std::endl << manip << st.text;
    return _out;
  }

  template<typename F>
  std::ostream& operator << ( const info<assert, F>& st )
  {
    _status_check();
    this->set_status_(unit_status::fail);
    _unit_counts.fails++;
    typename info<assert, F>::manip manip = fas_nullptr;
    _out << std::endl << manip << st.text;
    return _out;
  }

  template<typename F>
  std::ostream& operator << ( const info<critical, F>& st )
  {
    _status_check();
    this->set_status_(unit_status::fatal);
    _unit_counts.fatals++;
    typename info<critical, F>::manip manip = fas_nullptr;
    _out << std::endl << manip << st.text;
    return _out;
  }


  bool ok() const
  {
    return _suite_counts.ok();
  }

  const unit_counts& current_unit_counts() const
  {
    return _unit_counts;
  }

  bool current_unit_ok() const
  {
    return _unit_counts.ok();
  }

  bool run(int argc, char* argv[])
  {
    return _run(*this, argc, argv);
  }

  int get_argc() const { return _argc;}
  char** get_argv() const { return _argv;}
  std::string get_arg(int n) const
  {
    if ( n < _argc)
      return std::string(_argv[n]);
    return std::string();
  }


  static int size() { return length<unit_tag_list>::value;}
  int units_total() const { return _suite_counts.units_total; }

  int errors() const { return _suite_counts.errors; }
  int fails() const { return _suite_counts.fails; }
  int fatals() const { return _suite_counts.fatals; }

  const suite_counts& counts() const { return _suite_counts; }

public:
  void set_status_( unit_status::type status)
  {
    if ( status > _status )
      _status = status;
  }

  template<typename T>
  bool _run(T& t, int argc, char* argv[])
  {
    _argc = argc;
    _argv = argv;
    _unit_counts = unit_counts();
    _out << SUITE_BEG << this->size() << " tests";
    if (!_name.empty()) _out << " from " << _name;
    _out << ".";

    super::get_aspect().template getg<_units_>().for_each(t, f_unit_run() );
    _out << std::endl;

    if ( this->ok() )
    {
      _out << SUITE_END << std::endl;
      _out << PASSED << _suite_counts.units_passed << " tests." << std::endl;
    }
    else
    {
      _out << SUITE_FAIL << "Suite '" << _name << "' fail. " << _desc << std::endl;
      _out << RED_PASSED << _suite_counts.units_passed << " tests." << std::endl;
      _out << FAIL << _suite_counts.units_total - _suite_counts.units_passed << " tests." << std::endl;
    }
    return this->ok();
  }

private:

  std::ostream& _out;
  std::stringstream _stub;

  std::string _name;
  std::string _desc;
  unit_status::type _status;
  unit_counts  _unit_counts;
  suite_counts _suite_counts;

  int _argc;
  char** _argv;
};

}}

#include <fas/aop/aspect.hpp>

#define GET_REF(name) t.get_aspect().template get<name>()
#define GET_TYPE(name) typename T::aspect::template advice_cast<name>::type
#define GET_UNIT(name) t.get_aspect().template get<fas_##name##_tag>()
#define RUN_UNIT(name) t.get_aspect().template get<fas_##name##_tag>()(t)


#define BEGIN_UNIT_LIST(name) struct fas_##name##_unit_list: ::fas::type_list_n< ::fas::stub< ::fas::testing::_suite_stub_>
#define END_UNIT_LIST(name) >::type {};


#define BEGIN_SUITE(name, desc)\
  inline const char* fas_##name##_suite_desc() { return desc;}\
  struct fas_##name##_suite_aspect: ::fas::aspect< ::fas::type_list_n< ::fas::stub< ::fas::testing::_suite_stub_>

#define ADD_UNIT(name) , fas_##name##_type_list
#define ADD_CLASS(name) , ::fas::advice<name, name>
#define ADD_ADVICE(tag, name) , ::fas::advice<tag, name>
#define ADD_VALUE(tag, name) , ::fas::value<tag, name>
#define ADD_TYPE(tag, name) , ::fas::type<tag, name>
#define ADD_GROUP(tag, tag_list) , ::fas::group<tag, tag_list>
#define ADD_STUB(tag) , ::fas::stub<tag>
#define ADD_ASPECT(aspect) , aspect
#define ADD_UNIT_LIST(name) , fas_##name##_unit_list

#define END_SUITE(name) >::type > {}; \
struct fas_##name##_suite: ::fas::testing::suite<fas_##name##_suite_aspect> {\
  typedef ::fas::testing::suite<fas_##name##_suite_aspect> super;\
  bool run(int argc, char* argv[]) { return super::_run(*this, argc, argv); }\
  fas_##name##_suite(const std::string& name = "", const std::string& desc = ""): super(name, desc) {}\
  explicit fas_##name##_suite(std::ostream& os, const std::string& name = "", const std::string& desc = ""): super(os, name, desc) {}\
};\
::fas::testing::suite_counts fas_##name##_suite_run(int , char*[]);\
::fas::testing::suite_counts fas_##name##_suite_run(int argc, char* argv[])\
{\
  fas_##name##_suite s(#name, fas_##name##_suite_desc() );\
  s.run(argc, argv); \
  return s.counts();\
}



#endif

