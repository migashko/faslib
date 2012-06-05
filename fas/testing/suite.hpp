#ifndef FAS_TESTING_SUITE_HPP
#define FAS_TESTING_SUITE_HPP

#include <fas/testing/statements.hpp>
#include <fas/testing/formatting.hpp>
#include <fas/testing/exceptions.hpp>
#include <fas/testing/unit.hpp>
#include <fas/testing/tags.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/type_advice.hpp>
#include <fas/aop/value_advice.hpp>
#include <fas/aop/stub.hpp>
#include <fas/aop/group.hpp>
#include <fas/aop/aspect_class.hpp>
#include <fas/aop/tag.hpp>

#include <sstream>
#include <iostream>

namespace fas{ namespace testing{



struct suite_counts
  : unit_counts
{
  int units;
  int units_total;
  int units_passed;
  
  suite_counts()
    : unit_counts()
    , units()
    , units_total()
    , units_passed()
  {
  }
  
  void operator += ( const suite_counts& c )
  {
    unit_counts::operator += (c);
    units += c.units;
    units_total += c.units_total;
    units_passed += c.units_passed;
  }
  
  void operator += ( const unit_counts& c )
  {
    unit_counts::operator += (c);
  }
  
  operator bool () const
  {
    return units - units_passed == 0;
  }
};

struct f_unit_run
{
  /*
  template<typename T, typename Tg, typename U>
  void operator()(T& t, tag<Tg>, U& u)
  {
    t.out() << RUN << u.name() << std::endl;
    try
    {
      t.unit_begin(u);
      u(t);
      t.unit_end(u);
    }
    catch(const fail_error& )
    {
      //this->print_fail(t, u);
    }
    catch(const fatal_error&)
    {
      this->print_fail(t, u);
      throw;
    }
    catch(const std::exception& e)
    {
      t.out() << EXCEPT << e.what() << std::endl;
      this->print_fail(t, u);
      throw;
    }
    catch(...)
    {
      t.out() << EXCEPT << "Unhandled exception." << std::endl;
      this->print_fail(t, u);
      throw;
    }
    
    if (u)
      t.out() << OK << std::endl;
    else
      this->print_fail(t, u);
    // t.out() << UNIT_FAIL << u.desc()<< std::endl;
  }
  */

  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    typename T::aspect::template advice_cast<Tg>::type &u = t.get_aspect().template get<Tg>();
    
    t.out() << RUN << u.name() << std::endl;
    try
    {
      t.unit_begin(u);
      u(t);
      t.unit_end(u);
    }
    catch(const fail_error& )
    {
      // this->print_fail(t, u);
      t.unit_end(u);
      //throw;
    }
    catch(const fatal_error&)
    {
      this->print_fail(t, u);
      throw;
    }
    catch(const std::exception& e)
    {
      t.out() << EXCEPT << e.what() << std::endl;
      this->print_fail(t, u);
      throw;
    }
    catch(...)
    {
      t.out() << EXCEPT << "Unhandled exception." << std::endl;
      this->print_fail(t, u);
      throw;
    }
    
    if (u)
      t.out() << OK << std::endl;
    else
      this->print_fail(t, u);
    
    // t.out() << UNIT_FAIL << u.desc()<< std::endl;
  }

  template<typename T, typename U>
  void print_fail(T& t, U& u)
  {
    t.out() << UNIT_FAIL << u.name() << std::endl;
    if ( !u.desc().empty() )
      t.out() << UNIT_FAIL << u.desc() << std::endl;
    t.out() << UNIT_FAIL << "statements: " << u.counts().statements << std::endl;
    if ( u.counts().errors!=0)
      t.out() << UNIT_FAIL << light_red << "errors: " << u.counts().errors << restore << std::endl;
    if ( u.counts().fails!=0)
      t.out() << UNIT_FAIL << light_red << "fails: " << u.counts().fails << restore << std::endl;
    if ( u.counts().fatals!=0)
      t.out() << UNIT_FAIL << light_red << "fatals: " << u.counts().fatals << restore << std::endl;
  }

};
  
struct unit_status
{
  typedef enum { noerror, trace, error, fail, fatal} type;
};

template<typename A = ::fas::aspect<> >
class suite
  : public aspect_class< ::fas::aspect<>, A>
{

public:
  typedef suite<A> self;
  typedef aspect_class< ::fas::aspect<>, A> super;

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
    if ( _status != unit_status::noerror )
      /*_out <<std::endl*/;
    else
      _suite_counts.units_passed++;
    _suite_counts += u.counts();
    _suite_counts.units++;
    //_status_check();

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
    if ( _status != unit_status::noerror )
      _out << std::endl;
    _status_check();
    _status = unit_status::noerror;
  }

  void operator << ( void (*)( _stop_ ) )
  {
    statement_begin();
  }

  std::ostream& operator << ( const statement<expect>& st )
  {
    statement_begin();
    if ( st.result == false)
    {
      _unit_errors++;
      _status = unit_status::error;
      _out << ERROR_MESSAGE << st.text;
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
      _out << FAIL << st.text;
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
      _out << FATAL << st.text;
      return _out;
    }
    return _stub;
  }

  template<typename F>
  std::ostream& operator << ( const info<trace, F>& st )
  {
    statement_begin();
    _status = unit_status::trace;
    typename info<expect, F>::manip manip = 0;
    _out << manip << st.text;
    return _out;
  }

  template<typename F>
  std::ostream& operator << ( const info<expect, F>& st )
  {
    statement_begin();
    _status = unit_status::error;
    typename info<expect, F>::manip manip = 0;
    _out << manip << st.text;
    return _out;
  }

  template<typename F>
  std::ostream& operator << ( const info<assert, F>& st )
  {
    statement_begin();
    _status = unit_status::fail;
    typename info<assert, F>::manip manip = 0;
    _out << manip << st.text;
    return _out;
  }

  template<typename F>
  std::ostream& operator << ( const info<critical, F>& st )
  {
    statement_begin();
    _status = unit_status::fatal;
    typename info<critical, F>::manip manip = 0;
    _out << manip << st.text;
    return _out;
  }

  operator bool () const { return _suite_counts.errors == 0 &&  _suite_counts.fails==0 && _suite_counts.fatals==0;}

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
    _out << "." << std::endl;
    try
    {
      super::get_aspect().template getg<_units_>().for_each(t, f_unit_run() );
    }
    catch(const fail_error& )
    {
    }
    catch(const fatal_error& e)
    {
      throw e;
    }
   
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
 /*
 std::string_stream _current;
 bool _current_result;
 */
};

inline void show_total_result( const suite_counts& sc )
{
  if (!sc)
    std::cout << ::fas::light_red ;
  else
    std::cout << ::fas::green ;
  
  std::cout << "**************************************" << std::endl;
  std::cout << "units: " << sc.units << std::endl;
  if (!sc)
  {
    //std::cout << "units passed: " << sc.units_passed << std::endl;
    //std::cout << ::fas::red ;
    std::cout << ::fas::red  << "units fails: " << sc.units-sc.units_passed << ::fas::light_red  << std::endl;
    //std::cout << ::fas::light_red ;
  }
  
  std::cout << "statements: " << sc.statements << std::endl;
  if (!sc)
  {
    if (sc.errors!=0) std::cout << ::fas::red ;
    std::cout << "errors: " << sc.errors << ::fas::light_red << std::endl;
    if (sc.fails!=0) std::cout << ::fas::red ;
    std::cout << "fails: " << sc.fails << ::fas::light_red << std::endl;
    if (sc.fatals!=0) std::cout << ::fas::red ;
    std::cout << "fatals: " << sc.fatals << ::fas::light_red << std::endl;
  }
  std::cout << "**************************************" << std::endl;
  std::cout << ::fas::restore ;
  std::cout << std::endl;
  
  
}


}}

#include <fas/aop/aspect.hpp>
//#include <fas/type_list/tl.hpp>

#define ADD_UNIT(name) ,name##_type_list
#define ADD_CLASS(name) , ::fas::advice<name, name>
#define ADD_ADVICE(tag, name) , ::fas::advice<tag, name>
#define ADD_VALUE_ADVICE(tag, name) , ::fas::value_advice<tag, name>
#define ADD_TYPE_ADVICE(tag, name) , ::fas::type_advice<tag, name>
#define ADD_GROUP(tag, tag_list) , ::fas::group<tag, tag_list>
#define ADD_STUB(tag) , ::fas::stub<tag>
#define ADD_ASPECT(aspect) , aspect

#define GET_REF(name) t.get_aspect().template get<name>()
#define GET_TYPE(name) typename T::aspect::template advice_cast<name>::type


#define BEGIN_SUITE(name, desc)\
inline const char* name##_suite_desc() { return desc;}\
struct name##_suite_aspect: ::fas::aspect< ::fas::type_list_n< ::fas::stub< ::fas::testing::_suite_stub_>
// typedef ::fas::testing::suite< ::fas::aspect< ::fas::type_list_n< ::fas::stub< ::fas::testing::_suite_stub_>

// #define END_SUITE(name) >::type > > name##_suite;


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
/*
#define END_SUITE(name) >::type > {}; typedef ::fas::testing::suite<name##_suite_aspect> name##_suite;\
::fas::testing::suite_counts name##_suite_run(int , char*[])\
{\
  name##_suite s(#name, name##_suite_desc() );\
  s.run(); \
  return s.counts();\
}*/



#define BEGIN_TEST ::fas::testing::suite_counts fas_testing(int argc, char* argv[]) { ::fas::testing::suite_counts sc;
#define END_TEST show_total_result(sc); return sc;}

#define RUN_SUITE(name) ::fas::testing::suite_counts name##_suite_run(int argc, char* argv[]); sc+=name##_suite_run(argc, argv);
/*
inline const char* name_suite_desc() { return #desc;}
typedef suite< aspect< tl_n< el

>::type > >  name_suite;

int name_suite_run(int argc, char* argv[])
{
  name_suite s(#name, name_suite_desc() );
  s.run();
}
*/



#endif

