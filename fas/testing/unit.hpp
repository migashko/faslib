#ifndef FAS_TESTING_UNIT_HPP
#define FAS_TESTING_UNIT_HPP

#include <string>
#include <fas/aop/advice.hpp>
#include <fas/aop/group.hpp>
//#include <fas/type_list/tl.hpp>
#include <fas/testing/tags.hpp>

namespace fas{ namespace testing{

struct counts
{
  int errors;
  int fails;
  int fatals;
  
  counts()
    : errors()
    , fails()
    , fatals()
  {}
  
  void operator += ( const counts& c )
  {
    errors += c.errors;
    fails += c.fails;
    fatals += c.fatals;
  }
  
  operator bool () const
  {
    return errors==0 && fails==0 && fatals==0;
  }
};

struct unit_counts 
  : counts
{
  int statements;
  unit_counts()
    : counts()
    , statements()
  {}

  void operator += ( const unit_counts & c )
  {
    counts::operator += (c);
    statements += c.statements;
  }
};

class unit
{
  std::string _name;
  std::string _desc;
  unit_counts _counts;
  

public:
  unit(const std::string& name = "", const std::string& desc = "")
   : _name(name), _desc(desc), _counts()
  {
  }

  const std::string& name() const { return _name; }
  const std::string& desc() const { return _desc; }
  
  const unit_counts& counts() const { return _counts; }
  unit_counts& counts() { return _counts; }
  
  operator bool () const { return 0 == (_counts.errors + _counts.fails + _counts.fatals); }
};

}}

#define UNIT(name, desc)\
struct name##_unit: ::fas::testing::unit\
{ \
  name##_unit(): unit( #name, desc) { }\
\
  template<typename T>\
  void operator()(T& t);\
};\
\
struct name;\
struct name##_type_list: ::fas::type_list< ::fas::advice<name, name##_unit>, ::fas::type_list< ::fas::group< ::fas::testing::_units_, name> > > {};\
template<typename T>\
void name##_unit::operator()(T& t)

// typedef ::fas::type_list< ::fas::advice<name, name##_unit>, ::fas::type_list< ::fas::group< ::fas::testing::_units_, name> > > name##_type_list;

#endif
